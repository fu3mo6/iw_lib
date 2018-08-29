#ifndef _IW_WIPHY_H_
#define _IW_WIPHY_H_

#include <string>
#include <map>
#include "iw_util.h"

class WiFiIface {	
public:
  WiFiIface(){}
	~WiFiIface(){}
	
	std::string name;
	std::string phyID;
	bool is_enabled;
	std::string ssid;
	std::string op_mode;
	std::string macaddr;
	unsigned int ifidx;
	unsigned int freq;
	unsigned int chan;
	std::string width;
	unsigned int txpower;	
};

class WiPhy {
public:	
  WiPhy(){}
	~WiPhy(){}

	unsigned int id;
	std::map<std::string, WiFiIface> wifi_iface_map;
};

int WiPhy_handler(struct nl_msg *msg, void *arg);

#endif