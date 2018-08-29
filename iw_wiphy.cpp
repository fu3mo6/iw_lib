
#include "iw_wiphy.h"
#include "iw_util.h"

#define MAX_SSID_LEN 64
static std::string get_ssid_escaped(const uint8_t len, const uint8_t *data)
{
	int i;
	int pos = 0;
	char result[MAX_SSID_LEN] = "";

	for (i = 0; i < len; i++) {
		if (isprint(data[i]) && data[i] != ' ' && data[i] != '\\')
			pos += snprintf(result+pos, MAX_SSID_LEN-pos, "%c", data[i]);
		else if (data[i] == ' ' && (i != 0 && i != len -1))
			pos += snprintf(result+pos, MAX_SSID_LEN-pos, " ");
		else			
			pos += snprintf(result+pos, MAX_SSID_LEN-pos, "\\x%.2x", data[i]);
	}
	return std::string(result);
}

int WiPhy_handler(struct nl_msg *msg, void *arg)
{
	struct genlmsghdr *gnlh = (struct genlmsghdr *)nlmsg_data(nlmsg_hdr(msg));
	struct nlattr *tb_msg[NL80211_ATTR_MAX + 1];
	WiPhy* wiphy = (WiPhy*) arg;
	WiFiIface *iface;
	std::string ifname;

	if(!wiphy)
		return NL_SKIP;

	nla_parse(tb_msg, NL80211_ATTR_MAX, genlmsg_attrdata(gnlh, 0),
		  genlmsg_attrlen(gnlh, 0), NULL);

	if (tb_msg[NL80211_ATTR_WIPHY]) {
		wiphy->id = nla_get_u32(tb_msg[NL80211_ATTR_WIPHY]);
	}

	if (tb_msg[NL80211_ATTR_IFNAME]){
		ifname = nla_get_string(tb_msg[NL80211_ATTR_IFNAME]);
		iface = &wiphy->wifi_iface_map[ifname];
		iface->name = ifname;
	}
	else {
		printf("Unnamed/non-netdev interface not supported\n");
		return NL_SKIP;
	}
	
	if (tb_msg[NL80211_ATTR_IFINDEX]){
		iface->ifidx = nla_get_u32(tb_msg[NL80211_ATTR_IFINDEX]);
	}

	/*
	if (tb_msg[NL80211_ATTR_WDEV])
		printf("%s\twdev 0x%llx\n", indent,
		       (unsigned long long)nla_get_u64(tb_msg[NL80211_ATTR_WDEV]));*/

	if (tb_msg[NL80211_ATTR_MAC]) {
		char mac_addr[20];
		mac_addr_n2a(mac_addr, (unsigned char*)nla_data(tb_msg[NL80211_ATTR_MAC]));
		iface->macaddr = mac_addr;		
	}
	else
		iface->macaddr = "";
	
	if (tb_msg[NL80211_ATTR_SSID]) {
		iface->ssid = get_ssid_escaped(nla_len(tb_msg[NL80211_ATTR_SSID]),
				   (unsigned char*)nla_data(tb_msg[NL80211_ATTR_SSID]));
	}
	else
		iface->ssid = "";
	
	if (tb_msg[NL80211_ATTR_IFTYPE]){
			iface->op_mode = iftype_name((enum nl80211_iftype)nla_get_u32(tb_msg[NL80211_ATTR_IFTYPE]));
	}
	else
		iface->op_mode = "";
	
	if (tb_msg[NL80211_ATTR_WIPHY]){
		iface->phyID = nla_get_u32(tb_msg[NL80211_ATTR_WIPHY]);
	}
	
	if (tb_msg[NL80211_ATTR_WIPHY_FREQ]) {
		iface->freq = nla_get_u32(tb_msg[NL80211_ATTR_WIPHY_FREQ]);
		iface->chan = ieee80211_frequency_to_channel(iface->freq);

		if (tb_msg[NL80211_ATTR_CHANNEL_WIDTH]) {
			iface->width = channel_width_name((nl80211_chan_width)nla_get_u32(tb_msg[NL80211_ATTR_CHANNEL_WIDTH]));
		}
	}

	if (tb_msg[NL80211_ATTR_WIPHY_TX_POWER_LEVEL]) {
		iface->txpower = nla_get_u32(tb_msg[NL80211_ATTR_WIPHY_TX_POWER_LEVEL]);
	}
  /*
	if (tb_msg[NL80211_ATTR_TXQ_STATS]) {
		char buf[150];
		parse_txq_stats(buf, sizeof(buf), tb_msg[NL80211_ATTR_TXQ_STATS], 1, -1, indent);
		printf("%s\tmulticast TXQ:%s\n", indent, buf);
	}*/

	return NL_SKIP;
}
