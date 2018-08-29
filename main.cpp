
#include <string>
#include <iostream>
#include "iw_util.h"
#include "iw_wiphy.h"

using namespace std;

int main(int argc, char *argv[]) {
	string test_cmd = "iw dev";
	WiPhy wiphy;
	exec_iw(test_cmd, WiPhy_handler, &wiphy);

	map<string, WiFiIface>::iterator it;
	
	cout<<"phy "<<wiphy.id<<":"<<endl;
	for(it = wiphy.wifi_iface_map.begin(); it != wiphy.wifi_iface_map.end(); it++){
		cout<<"\t name: " << it->second.name << endl;
		cout<<"\t op_mode: " << it->second.op_mode <<endl;
		cout<<"\t macaddr: " << it->second.macaddr <<endl;
		cout<<"\t ifidx: " << it->second.ifidx <<endl;
		cout<<"\t freq: " << it->second.freq <<endl;
		cout<<"\t chan: " << it->second.chan <<endl;
		cout<<"\t width: " << it->second.width <<endl;
		cout<<"\t txpower: " << it->second.txpower << " mbm" << endl;
	}
	
	return 0;
}