#include <ctime>
#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include "ns3/core-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/ipv4.h"
#include "ns3/udp-echo-server.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"
#include "ns3/netanim-module.h"
#include "ns3/ipv4-global-routing-helper.h"
#include "ns3/flow-monitor-helper.h"
#include "ns3/random-variable-stream.h"
#include "ns3/ipv4-flow-classifier.h"




using namespace ns3;
using namespace std;


	
double GenerateRandInterval(double num)
{	
	
	double value; 
	value = num * ((rand() + 1.0) / double(RAND_MAX + 2.0)); //generating random numbers between 0.0-0.1 
	return value;
	
}

double GenerateRandReply(double num)
{	
	
	double value2; 
	value2 = num * ((rand() + 1.0) / double(RAND_MAX + 2.0))+0.01; //generating random numbers between 0.01-0.05
	cout<<"Reply Time = "<<value2<<"\n"; 
	return value2;
	
}


int GenerateRandText(int TextSize)
{	
	
	int value3; 
	value3 = int(TextSize * ((rand() + 1.0) / double(RAND_MAX + 2.0))) + 1; //generating random numbers between 1-1000 by. 
	cout<<"Packet Size = "<<value3<<"\n";
	return value3;
}

NS_LOG_COMPONENT_DEFINE("DCNusingNS3");

int main(int argc, char *argv[])
{
	
	CommandLine cmd;
	bool ECMProuting = true;
	cmd.AddValue ("ECMProuting", "ECMP routing (To enable type 'true') ", ECMProuting);
	cmd.Parse (argc, argv);
	  
	Time::SetResolution (Time::NS);
	LogComponentEnable ("UdpEchoClientApplication", LOG_LEVEL_INFO);
	LogComponentEnable ("UdpEchoServerApplication", LOG_LEVEL_INFO);
	
	Config::SetDefault("ns3::Ipv4GlobalRouting::RandomEcmpRouting",BooleanValue(ECMProuting));
	
	
	
	uint32_t Corequeuesize,Leafqueuesize;
	Corequeuesize = 8;
	Leafqueuesize = 4;
	PointToPointHelper NodeToSW;
	NodeToSW.SetDeviceAttribute ("DataRate", StringValue ("10Gbps"));
	NodeToSW.SetChannelAttribute ("Delay", StringValue ("200ns"));
	
	PointToPointHelper SWToSW_50ns;
	SWToSW_50ns.SetDeviceAttribute ("DataRate", StringValue ("40Gbps"));
	SWToSW_50ns.SetChannelAttribute ("Delay", StringValue ("50ns"));
	SWToSW_50ns.SetQueue("ns3::DropTailQueue", "MaxPackets", UintegerValue(Corequeuesize)); 
	
	PointToPointHelper SWToSW_70ns;
	SWToSW_70ns.SetDeviceAttribute ("DataRate", StringValue ("40Gbps"));
	SWToSW_70ns.SetChannelAttribute ("Delay", StringValue ("70ns"));
	SWToSW_70ns.SetQueue("ns3::DropTailQueue", "MaxPackets", UintegerValue(Leafqueuesize)); 
	
	NodeContainer pod0,pod1,pod2,pod3,core,sw0,sw1,sw2,sw3,sw4,sw5,sw6,sw7,sw8,sw9;
	pod0.Create (6);//eacd pod have got 6 servers
	pod1.Create (6);
	pod2.Create (6);
	pod3.Create (6);
	core.Create (1);//client layer
	Ptr<Node> A = core.Get(0);	
	sw0.Create(2);//neighbour switches
	sw1.Create (2);//neighbour switches
	sw2.Create (2);//neighbour switches
	sw3.Create (2);//neighbour switches
	sw4.Create(2);//neighbour switches
	sw5.Create (2);//neighbour switches
	sw6.Create (2);//neighbour switches
	sw7.Create (2);//neighbour switches
	sw8.Create (8);//top switches
	sw9.Create (8);//top switches
	
	
	InternetStackHelper Stack;
	Stack.Install( pod0);
	Stack.Install( pod1);
	Stack.Install( pod2);
	Stack.Install( pod3);
	Stack.Install (A);
	Stack.Install( sw0);
	Stack.Install( sw1);
	Stack.Install( sw2);
	Stack.Install( sw3);
	Stack.Install( sw4);
	Stack.Install( sw5);
	Stack.Install( sw6);
	Stack.Install( sw7);
	Stack.Install( sw8);
	Stack.Install( sw9);
	
	
	
	
	//Creating Topology

	NetDeviceContainer pod0_dev1,pod0_dev2,pod0_dev3,pod0_dev4,pod0_dev5,pod0_dev6,pod0_dev7,pod0_dev8,pod0_dev9,pod0_dev10,
        pod0_dev11,pod0_dev12,pod0_dev13,pod0_dev14,pod0_dev15,pod0_dev16,pod0_dev17,pod0_dev18,pod0_dev19,pod0_dev20,pod0_dev21,pod0_dev22,pod0_dev23,pod0_dev24,pod0_dev25,
        pod0_dev26,pod0_dev27,pod0_dev28,pod0_dev29,pod0_dev30,pod0_dev31,pod0_dev32;

	NetDeviceContainer Array_Links[32];
	
	Array_Links[0] = pod0_dev1;
	Array_Links[1] = pod0_dev2;
	Array_Links[2] = pod0_dev3;
	Array_Links[3] = pod0_dev4;
	Array_Links[4] = pod0_dev5;
	Array_Links[5] = pod0_dev6;
	Array_Links[6] = pod0_dev7;
	Array_Links[7] = pod0_dev8;
	Array_Links[8] = pod0_dev9;
	Array_Links[9] = pod0_dev10;
	Array_Links[10] = pod0_dev11;
	Array_Links[11] = pod0_dev12;	
	Array_Links[12] = pod0_dev13;
	Array_Links[13] = pod0_dev14;
	Array_Links[14] = pod0_dev15;
	Array_Links[15] = pod0_dev16;
	Array_Links[16] = pod0_dev17;
	Array_Links[17] = pod0_dev18;
	Array_Links[18] = pod0_dev19;
	Array_Links[19] = pod0_dev20;
	Array_Links[20] = pod0_dev21;
	Array_Links[21] = pod0_dev22;
	Array_Links[22] = pod0_dev23;
	Array_Links[23] = pod0_dev24;
	Array_Links[24] = pod0_dev25;
	Array_Links[25] = pod0_dev26;
	Array_Links[26] = pod0_dev27;
	Array_Links[27] = pod0_dev28;
	Array_Links[28] = pod0_dev29;
	Array_Links[29] = pod0_dev30;
	Array_Links[30] = pod0_dev31;
	Array_Links[31] = pod0_dev32;
		
	/*int k=0;
	while(k<12)
	for(int i=0;i<6;i++)
		{
			for(int j=0;j<2;j++)
				{
					Array_Links[k]=NodeToSW.Install( pod0.Get(i), sw0.Get(j));
					k++;
				}		
		}*/
	
	pod0_dev1 = NodeToSW.Install( pod0.Get(0), sw0.Get(0));
	pod0_dev2 = NodeToSW.Install( pod0.Get(0), sw0.Get(1));	
	pod0_dev3 = NodeToSW.Install( pod0.Get(1), sw0.Get(0));
	pod0_dev4 = NodeToSW.Install( pod0.Get(1), sw0.Get(1));
	pod0_dev5 = NodeToSW.Install( pod0.Get(2), sw0.Get(0));
	pod0_dev6 = NodeToSW.Install( pod0.Get(2), sw0.Get(1));
	pod0_dev7 = NodeToSW.Install( pod0.Get(3), sw0.Get(0));
	pod0_dev8 = NodeToSW.Install( pod0.Get(3), sw0.Get(1));
	pod0_dev9 = NodeToSW.Install( pod0.Get(4), sw0.Get(0));
	pod0_dev10 = NodeToSW.Install( pod0.Get(4), sw0.Get(1));
	pod0_dev11 = NodeToSW.Install( pod0.Get(5), sw0.Get(0));
	pod0_dev12 = NodeToSW.Install( pod0.Get(5), sw0.Get(1));

	/*for(int i=13;i<20;i+=2)
		{
			if(i%2==0)
			{
			for(int j=0;j<8;j+=2)
				{
					Array_Links[i] = SWToSW_50ns.Install( pod0.Get(0), sw8.Get(j));
				}
			}	
		}
	for(int i=14;i<21;i+=2)
		{
			for(int j=4;j<8;j+=2)
				{
					Array_Links[i]=SWToSW_70ns.Install( pod0.Get(0), sw8.Get(j));
				}	
		}*/
	
	pod0_dev13 = SWToSW_50ns.Install( sw0.Get(0), sw8.Get(0));
	pod0_dev14 = SWToSW_70ns.Install( sw0.Get(0), sw8.Get(1));
	pod0_dev15 = SWToSW_50ns.Install( sw0.Get(0), sw8.Get(2));
	pod0_dev16 = SWToSW_70ns.Install( sw0.Get(0), sw8.Get(3));
	pod0_dev17 = SWToSW_50ns.Install( sw0.Get(1), sw8.Get(4));
	pod0_dev18 = SWToSW_70ns.Install( sw0.Get(1), sw8.Get(5));
	pod0_dev19 = SWToSW_50ns.Install( sw0.Get(1), sw8.Get(6));
	pod0_dev20 = SWToSW_70ns.Install( sw0.Get(1), sw8.Get(7));
	
	/*int a=21;
	while(a<32)
	for(int i=0;i<6;i++)
		{
			for(int j=0;j<2;j++)
				{
					Array_Links[a]=NodeToSW.Install( pod0.Get(a), sw9.Get(j));
					a++;
				}
			
		}*/

	pod0_dev21 = NodeToSW.Install( pod0.Get(0), sw9.Get(0));
	pod0_dev22 = NodeToSW.Install( pod0.Get(0), sw9.Get(1));
	pod0_dev23 = NodeToSW.Install( pod0.Get(1), sw9.Get(0));
	pod0_dev24 = NodeToSW.Install( pod0.Get(1), sw9.Get(1));
	pod0_dev25 = NodeToSW.Install( pod0.Get(2), sw9.Get(0));
	pod0_dev26 = NodeToSW.Install( pod0.Get(2), sw9.Get(1));
	pod0_dev27 = NodeToSW.Install( pod0.Get(3), sw9.Get(0));
	pod0_dev28 = NodeToSW.Install( pod0.Get(3), sw9.Get(1));
	pod0_dev29 = NodeToSW.Install( pod0.Get(4), sw9.Get(0));
	pod0_dev30 = NodeToSW.Install( pod0.Get(4), sw9.Get(1));
	pod0_dev31 = NodeToSW.Install( pod0.Get(5), sw9.Get(0));
	pod0_dev32 = NodeToSW.Install( pod0.Get(5), sw9.Get(1));		
	
	NetDeviceContainer pod1_dev,pod1_dev2,pod1_dev3,pod1_dev4,pod1_dev5,pod1_dev6,pod1_dev7,pod1_dev8,pod1_dev9,pod1_dev10,
	pod1_dev11,pod1_dev12,pod1_dev13,pod1_dev14,pod1_dev15,pod1_dev16,pod1_dev17,pod1_dev18,pod1_dev19,pod1_dev20,pod1_dev21,pod1_dev22,pod1_dev23,pod1_dev24,pod1_dev25,pod1_dev26,
	pod1_dev27,pod1_dev28,pod1_dev29,pod1_dev30,pod1_dev31,pod1_dev32;
	
	pod1_dev = NodeToSW.Install( pod1.Get(0), sw1.Get(0));
	pod1_dev2 = NodeToSW.Install( pod1.Get(0), sw1.Get(1));
	pod1_dev3 = NodeToSW.Install( pod1.Get(1), sw1.Get(0));
	pod1_dev4 = NodeToSW.Install( pod1.Get(1), sw1.Get(1));
	pod1_dev5 = NodeToSW.Install( pod1.Get(2), sw1.Get(0));
	pod1_dev6 = NodeToSW.Install( pod1.Get(2), sw1.Get(1));
	pod1_dev7 = NodeToSW.Install( pod1.Get(3), sw1.Get(0));
	pod1_dev8 = NodeToSW.Install( pod1.Get(3), sw1.Get(1));
	pod1_dev9 = NodeToSW.Install( pod1.Get(4), sw1.Get(0));
	pod1_dev10 = NodeToSW.Install( pod1.Get(4), sw1.Get(1));
	pod1_dev11 = NodeToSW.Install( pod1.Get(5), sw1.Get(0));
	pod1_dev12 = NodeToSW.Install( pod1.Get(5), sw1.Get(1));
	pod1_dev13 = SWToSW_50ns.Install( sw1.Get(0), sw8.Get(0));
	pod1_dev14 = SWToSW_70ns.Install( sw1.Get(0), sw8.Get(1));
	pod1_dev15 = SWToSW_50ns.Install( sw1.Get(0), sw8.Get(2));
	pod1_dev16 = SWToSW_70ns.Install( sw1.Get(0), sw8.Get(3));
	pod1_dev17 = SWToSW_50ns.Install( sw1.Get(1), sw8.Get(4));
	pod1_dev18 = SWToSW_70ns.Install( sw1.Get(1), sw8.Get(5));
	pod1_dev19 = SWToSW_50ns.Install( sw1.Get(1), sw8.Get(6));
	pod1_dev20 = SWToSW_70ns.Install( sw1.Get(1), sw8.Get(7));
	pod1_dev21 = NodeToSW.Install( pod1.Get(0), sw9.Get(2));
	pod1_dev22 = NodeToSW.Install( pod1.Get(0), sw9.Get(3));
	pod1_dev23 = NodeToSW.Install( pod1.Get(1), sw9.Get(2));
	pod1_dev24 = NodeToSW.Install( pod1.Get(1), sw9.Get(3));
	pod1_dev25 = NodeToSW.Install( pod1.Get(2), sw9.Get(2));
	pod1_dev26 = NodeToSW.Install( pod1.Get(2), sw9.Get(3));
	pod1_dev27 = NodeToSW.Install( pod1.Get(3), sw9.Get(2));
	pod1_dev28 = NodeToSW.Install( pod1.Get(3), sw9.Get(3));
	pod1_dev29 = NodeToSW.Install( pod1.Get(4), sw9.Get(2));
	pod1_dev30 = NodeToSW.Install( pod1.Get(4), sw9.Get(3));
	pod1_dev31 = NodeToSW.Install( pod1.Get(5), sw9.Get(2));
	pod1_dev32 = NodeToSW.Install( pod1.Get(5), sw9.Get(3));
	
	NetDeviceContainer pod2_dev,pod2_dev2,pod2_dev3,pod2_dev4,pod2_dev5,pod2_dev6,pod2_dev7,pod2_dev8,pod2_dev9,pod2_dev10,
	pod2_dev11,pod2_dev12,pod2_dev13,pod2_dev14,pod2_dev15,pod2_dev16,pod2_dev17,pod2_dev18,pod2_dev19,pod2_dev20,pod2_dev21,pod2_dev22,pod2_dev23,pod2_dev24,pod2_dev25,
	pod2_dev26,pod2_dev27,pod2_dev28,pod2_dev29,pod2_dev30,pod2_dev31,pod2_dev32;
	
	pod2_dev = NodeToSW.Install( pod2.Get(0), sw2.Get(0));
	pod2_dev2 = NodeToSW.Install( pod2.Get(0), sw2.Get(1));
	pod2_dev3 = NodeToSW.Install( pod2.Get(1), sw2.Get(0));
	pod2_dev4 = NodeToSW.Install( pod2.Get(1), sw2.Get(1));
	pod2_dev5 = NodeToSW.Install( pod2.Get(2), sw2.Get(0));
	pod2_dev6 = NodeToSW.Install( pod2.Get(2), sw2.Get(1));
	pod2_dev7 = NodeToSW.Install( pod2.Get(3), sw2.Get(0));
	pod2_dev8 = NodeToSW.Install( pod2.Get(3), sw2.Get(1));
	pod2_dev9 = NodeToSW.Install( pod2.Get(4), sw2.Get(0));
	pod2_dev10 = NodeToSW.Install( pod2.Get(4), sw2.Get(1));
	pod2_dev11 = NodeToSW.Install( pod2.Get(5), sw2.Get(0));
	pod2_dev12 = NodeToSW.Install( pod2.Get(5), sw2.Get(1));
	pod2_dev13 = SWToSW_50ns.Install( sw2.Get(0), sw8.Get(0));
	pod2_dev14 = SWToSW_70ns.Install( sw2.Get(0), sw8.Get(1));
	pod2_dev15 = SWToSW_50ns.Install( sw2.Get(0), sw8.Get(2));
	pod2_dev16 = SWToSW_70ns.Install( sw2.Get(0), sw8.Get(3));
	pod2_dev17 = SWToSW_50ns.Install( sw2.Get(1), sw8.Get(4));
	pod2_dev18 = SWToSW_70ns.Install( sw2.Get(1), sw8.Get(5));
	pod2_dev19 = SWToSW_50ns.Install( sw2.Get(1), sw8.Get(6));
	pod2_dev20 = SWToSW_70ns.Install( sw2.Get(1), sw8.Get(7));
	pod2_dev21 = NodeToSW.Install( pod2.Get(0), sw9.Get(4));
	pod2_dev22 = NodeToSW.Install( pod2.Get(0), sw9.Get(5));
	pod2_dev23 = NodeToSW.Install( pod2.Get(1), sw9.Get(4));
	pod2_dev24 = NodeToSW.Install( pod2.Get(1), sw9.Get(5));
	pod2_dev25 = NodeToSW.Install( pod2.Get(2), sw9.Get(4));
	pod2_dev26 = NodeToSW.Install( pod2.Get(2), sw9.Get(5));
	pod2_dev27 = NodeToSW.Install( pod2.Get(3), sw9.Get(4));
	pod2_dev28 = NodeToSW.Install( pod2.Get(3), sw9.Get(5));
	pod2_dev29 = NodeToSW.Install( pod2.Get(4), sw9.Get(4));
	pod2_dev30 = NodeToSW.Install( pod2.Get(4), sw9.Get(5));
	pod2_dev31 = NodeToSW.Install( pod2.Get(5), sw9.Get(4));
	pod2_dev32 = NodeToSW.Install( pod2.Get(5), sw9.Get(5));	

	NetDeviceContainer pod3_dev,pod3_dev2,pod3_dev3,pod3_dev4,pod3_dev5,pod3_dev6,pod3_dev7,pod3_dev8,pod3_dev9,pod3_dev10,
	pod3_dev11,pod3_dev12,pod3_dev13,pod3_dev14,pod3_dev15,pod3_dev16,pod3_dev17,pod3_dev18,pod3_dev19,pod3_dev20,pod3_dev21,pod3_dev22,pod3_dev23,pod3_dev24,pod3_dev25,
	pod3_dev26,pod3_dev27,pod3_dev28,pod3_dev29,pod3_dev30,pod3_dev31,pod3_dev32;
	
	pod3_dev = NodeToSW.Install( pod3.Get(0), sw3.Get(0));
	pod3_dev2 = NodeToSW.Install( pod3.Get(0), sw3.Get(1));
	pod3_dev3 = NodeToSW.Install( pod3.Get(1), sw3.Get(0));
	pod3_dev4 = NodeToSW.Install( pod3.Get(1), sw3.Get(1));
	pod3_dev5 = NodeToSW.Install( pod3.Get(2), sw3.Get(0));
	pod3_dev6 = NodeToSW.Install( pod3.Get(2), sw3.Get(1));
	pod3_dev7 = NodeToSW.Install( pod3.Get(3), sw3.Get(0));
	pod3_dev8 = NodeToSW.Install( pod3.Get(3), sw3.Get(1));
	pod3_dev9 = NodeToSW.Install( pod3.Get(4), sw3.Get(0));
	pod3_dev10 = NodeToSW.Install( pod3.Get(4), sw3.Get(1));
	pod3_dev11 = NodeToSW.Install( pod3.Get(5), sw3.Get(0));
	pod3_dev12 = NodeToSW.Install( pod3.Get(5), sw3.Get(1));
	pod3_dev13 = SWToSW_50ns.Install( sw3.Get(0), sw8.Get(0));
	pod3_dev14 = SWToSW_70ns.Install( sw3.Get(0), sw8.Get(1));
	pod3_dev15 = SWToSW_50ns.Install( sw3.Get(0), sw8.Get(2));
	pod3_dev16 = SWToSW_70ns.Install( sw3.Get(0), sw8.Get(3));
	pod3_dev17 = SWToSW_50ns.Install( sw3.Get(1), sw8.Get(4));
	pod3_dev18 = SWToSW_70ns.Install( sw3.Get(1), sw8.Get(5));
	pod3_dev19 = SWToSW_50ns.Install( sw3.Get(1), sw8.Get(6));
	pod3_dev20 = SWToSW_70ns.Install( sw3.Get(1), sw8.Get(7));
	pod3_dev21 = NodeToSW.Install( pod3.Get(0), sw9.Get(6));
	pod3_dev22 = NodeToSW.Install( pod3.Get(0), sw9.Get(7));
	pod3_dev23 = NodeToSW.Install( pod3.Get(1), sw9.Get(6));
	pod3_dev24 = NodeToSW.Install( pod3.Get(1), sw9.Get(7));
	pod3_dev25 = NodeToSW.Install( pod3.Get(2), sw9.Get(6));
	pod3_dev26 = NodeToSW.Install( pod3.Get(2), sw9.Get(7));
	pod3_dev27 = NodeToSW.Install( pod3.Get(3), sw9.Get(6));
	pod3_dev28 = NodeToSW.Install( pod3.Get(3), sw9.Get(7));
	pod3_dev29 = NodeToSW.Install( pod3.Get(4), sw9.Get(6));
	pod3_dev30 = NodeToSW.Install( pod3.Get(4), sw9.Get(7));
	pod3_dev31 = NodeToSW.Install( pod3.Get(5), sw9.Get(6));
	pod3_dev32 = NodeToSW.Install( pod3.Get(5), sw9.Get(7));


	NetDeviceContainer sw4_dev,sw4_dev2,sw4_dev3,sw4_dev4,sw4_dev5,sw4_dev6,sw4_dev7,sw4_dev8;
	sw4_dev = SWToSW_50ns.Install( sw4.Get(0), sw9.Get(0));
	sw4_dev2 = SWToSW_70ns.Install( sw4.Get(0), sw9.Get(1));
	sw4_dev3 = SWToSW_50ns.Install( sw4.Get(0), sw9.Get(2));
	sw4_dev4 = SWToSW_70ns.Install( sw4.Get(0), sw9.Get(3));
	sw4_dev5 = SWToSW_50ns.Install( sw4.Get(1), sw9.Get(4));	
	sw4_dev6 = SWToSW_70ns.Install( sw4.Get(1), sw9.Get(5));
	sw4_dev7 = SWToSW_50ns.Install( sw4.Get(1), sw9.Get(6));
	sw4_dev8 = SWToSW_70ns.Install( sw4.Get(1), sw9.Get(7));

	NetDeviceContainer sw5_dev,sw5_dev2,sw5_dev3,sw5_dev4,sw5_dev5,sw5_dev6,sw5_dev7,sw5_dev8;
	sw5_dev = SWToSW_50ns.Install( sw5.Get(0), sw9.Get(0));
	sw5_dev2 = SWToSW_70ns.Install( sw5.Get(0), sw9.Get(1));
	sw5_dev3 = SWToSW_50ns.Install( sw5.Get(0), sw9.Get(2));
	sw5_dev4 = SWToSW_70ns.Install( sw5.Get(0), sw9.Get(3));
	sw5_dev5 = SWToSW_50ns.Install( sw5.Get(1), sw9.Get(4));	
	sw5_dev6 = SWToSW_70ns.Install( sw5.Get(1), sw9.Get(5));
	sw5_dev7 = SWToSW_50ns.Install( sw5.Get(1), sw9.Get(6));
	sw5_dev8 = SWToSW_70ns.Install( sw5.Get(1), sw9.Get(7));	
	
	NetDeviceContainer sw6_dev,sw6_dev2,sw6_dev3,sw6_dev4,sw6_dev5,sw6_dev6,sw6_dev7,sw6_dev8;
	sw6_dev = SWToSW_50ns.Install( sw6.Get(0), sw9.Get(0));
	sw6_dev2 = SWToSW_70ns.Install( sw6.Get(0), sw9.Get(1));
	sw6_dev3 = SWToSW_50ns.Install( sw6.Get(0), sw9.Get(2));
	sw6_dev4 = SWToSW_70ns.Install( sw6.Get(0), sw9.Get(3));
	sw6_dev5 = SWToSW_50ns.Install( sw6.Get(1), sw9.Get(4));	
	sw6_dev6 = SWToSW_70ns.Install( sw6.Get(1), sw9.Get(5));
	sw6_dev7 = SWToSW_50ns.Install( sw6.Get(1), sw9.Get(6));
	sw6_dev8 = SWToSW_70ns.Install( sw6.Get(1), sw9.Get(7));

	NetDeviceContainer sw7_dev,sw7_dev2,sw7_dev3,sw7_dev4,sw7_dev5,sw7_dev6,sw7_dev7,sw7_dev8;
	sw7_dev = SWToSW_50ns.Install( sw7.Get(0), sw9.Get(0));
	sw7_dev2 = SWToSW_70ns.Install( sw7.Get(0), sw9.Get(1));
	sw7_dev3 = SWToSW_50ns.Install( sw7.Get(0), sw9.Get(2));
	sw7_dev4 = SWToSW_70ns.Install( sw7.Get(0), sw9.Get(3));
	sw7_dev5 = SWToSW_50ns.Install( sw7.Get(1), sw9.Get(4));	
	sw7_dev6 = SWToSW_70ns.Install( sw7.Get(1), sw9.Get(5));
	sw7_dev7 = SWToSW_50ns.Install( sw7.Get(1), sw9.Get(6));
	sw7_dev8 = SWToSW_70ns.Install( sw7.Get(1), sw9.Get(7));


	//Core router connections
	NetDeviceContainer core_dev1,core_dev2,core_dev3,core_dev4,core_dev5,core_dev6,core_dev7,core_dev8;
	NetDeviceContainer core_dev9,core_dev10,core_dev11,core_dev12,core_dev13,core_dev14,core_dev15,core_dev16; 
	
	NetDeviceContainer Array_Core[16];
	Array_Core[0]=core_dev1;
	Array_Core[1]=core_dev2;
	Array_Core[2]=core_dev3;
	Array_Core[3]=core_dev4;
	Array_Core[4]=core_dev5;
	Array_Core[5]=core_dev6;
	Array_Core[6]=core_dev7;
	Array_Core[7]=core_dev8;
	Array_Core[8]=core_dev9;
	Array_Core[9]=core_dev10;
	Array_Core[10]=core_dev11;
	Array_Core[11]=core_dev12;
	Array_Core[12]=core_dev13;
	Array_Core[13]=core_dev14;
	Array_Core[14]=core_dev15;
	Array_Core[15]=core_dev16;
	
	for(int i=0;i<8;i++)
	{

		Array_Core[i]=SWToSW_50ns.Install( sw8.Get(i), A);//core connection from 0 to 8
	}
	
	/*for(int i=8;i<16;i++)
	{	
		//if(i==8 || i==10 || i==12 || i==14)
		
			if(i==8)
			{
			Array_Core[i] = SWToSW_50ns.Install( sw4.Get(0), A);
			}
			else if (i==10)
			{
			Array_Core[i] = SWToSW_50ns.Install( sw5.Get(0), A);
			}
			else if (i==12)
			{
			Array_Core[i] = SWToSW_50ns.Install( sw6.Get(0), A);
			}
			else if (i==14)
			{
			Array_Core[i] = SWToSW_50ns.Install( sw7.Get(0), A);
			}
		
		//else if(i==9 || i==11 || i==13 || i==15)
		
			if(i==9)
			{
			Array_Core[i] = SWToSW_50ns.Install( sw4.Get(1), A);
			}
			else if (i==11)
			{
			Array_Core[i] = SWToSW_50ns.Install( sw5.Get(1), A);
			}
			else if (i==13)
			{
			Array_Core[i] = SWToSW_50ns.Install( sw6.Get(1), A);
			}
			else if (i==15)
			{
			Array_Core[i] = SWToSW_50ns.Install( sw7.Get(1), A);
			}
		

	}*/

	core_dev9 = SWToSW_50ns.Install( sw4.Get(0), A);
	core_dev10 = SWToSW_50ns.Install( sw4.Get(1), A);
	core_dev11 = SWToSW_50ns.Install( sw5.Get(0), A);
	core_dev12 = SWToSW_50ns.Install( sw5.Get(1), A);
	
	core_dev13 = SWToSW_50ns.Install( sw6.Get(0), A);
	core_dev14 = SWToSW_50ns.Install( sw6.Get(1), A);
	core_dev15 = SWToSW_50ns.Install( sw7.Get(0), A);
	core_dev16 = SWToSW_50ns.Install( sw7.Get(1), A);
	
	
	//Assigning the IP address
	
	Ipv4AddressHelper address;
	Ipv4InterfaceContainer pod0_Iface,pod0_Iface2,pod0_Iface3,pod0_Iface4,pod0_Iface5,pod0_Iface6,pod0_Iface7,pod0_Iface8,pod0_Iface9,pod0_Iface10,
	pod0_Iface11,pod0_Iface12,pod0_Iface13,pod0_Iface14,pod0_Iface15,pod0_Iface16,pod0_Iface17,pod0_Iface18,pod0_Iface19,pod0_Iface20,pod0_Iface21,
	pod0_Iface22,pod0_Iface23,pod0_Iface24,pod0_Iface25,pod0_Iface26,pod0_Iface27,pod0_Iface28,pod0_Iface29,pod0_Iface30,pod0_Iface31,pod0_Iface32;		
	
	address.SetBase("10.0.1.0","255.255.255.0");
	pod0_Iface = address.Assign(pod0_dev1);
	
	address.SetBase("10.0.2.0","255.255.255.0");
	pod0_Iface2 = address.Assign(pod0_dev2);
	
	address.SetBase("10.0.3.0","255.255.255.0");
	pod0_Iface3 = address.Assign(pod0_dev3);
	
	address.SetBase("10.1.0.0","255.255.255.0");
	pod0_Iface4 = address.Assign(pod0_dev4);
	
	address.SetBase("10.2.0.0","255.255.0.0");
	pod0_Iface5 = address.Assign(pod0_dev5);

	address.SetBase("10.3.0.0","255.255.0.0");
	pod0_Iface6 = address.Assign(pod0_dev6);

	address.SetBase("10.2.1.0","255.255.255.0");
	pod0_Iface7 = address.Assign(pod0_dev7);

	address.SetBase("10.3.1.0","255.255.255.0");
	pod0_Iface8 = address.Assign(pod0_dev8);
	
	address.SetBase("10.2.2.0","255.255.255.0");
	pod0_Iface9 = address.Assign(pod0_dev9);
	
	address.SetBase("10.3.2.0","255.255.255.0");
	pod0_Iface10 = address.Assign(pod0_dev10);

	address.SetBase("10.3.3.0","255.255.255.0");
	pod0_Iface11 = address.Assign(pod0_dev11);
	
	address.SetBase("10.4.0.0","255.255.255.0");
	pod0_Iface12 = address.Assign(pod0_dev12);
	
	address.SetBase("10.4.1.0","255.255.255.0");
	pod0_Iface13 = address.Assign(pod0_dev13);

	address.SetBase("10.4.2.0","255.255.255.0");
	pod0_Iface14 = address.Assign(pod0_dev14);
	
	address.SetBase("10.4.3.0","255.255.255.0");
	pod0_Iface15 = address.Assign(pod0_dev15);

	address.SetBase("10.4.4.0","255.255.255.0");
	pod0_Iface16 = address.Assign(pod0_dev16);

	address.SetBase("10.5.0.0","255.255.255.0");
	pod0_Iface17 = address.Assign(pod0_dev17);
		
	address.SetBase("10.5.1.0","255.255.255.0");
	pod0_Iface18 = address.Assign(pod0_dev18);
	
	address.SetBase("10.5.2.0","255.255.255.0");
	pod0_Iface19 = address.Assign(pod0_dev19);

	address.SetBase("10.5.3.0","255.255.255.0");
	pod0_Iface20 = address.Assign(pod0_dev20);
	
	address.SetBase("10.7.2.0","255.255.255.0");
	pod0_Iface21 = address.Assign(pod0_dev21);
	
	address.SetBase("10.5.4.0","255.255.255.0");
	pod0_Iface22 = address.Assign(pod0_dev22);
	
	address.SetBase("10.5.5.0","255.255.255.0");
	pod0_Iface23 = address.Assign(pod0_dev23);
	
	address.SetBase("10.6.0.0","255.255.255.0");
	pod0_Iface24 = address.Assign(pod0_dev24);

	address.SetBase("10.6.1.0","255.255.255.0");
	pod0_Iface25 = address.Assign(pod0_dev25);
	
	address.SetBase("10.6.2.0","255.255.255.0");
	pod0_Iface26 = address.Assign(pod0_dev26);

	address.SetBase("10.6.3.0","255.255.255.0");
	pod0_Iface27 = address.Assign(pod0_dev27);
	
	address.SetBase("10.6.4.0","255.255.255.0");
	pod0_Iface28 = address.Assign(pod0_dev28);

	address.SetBase("10.6.5.0","255.255.255.0");
	pod0_Iface29 = address.Assign(pod0_dev29);
	
	address.SetBase("10.6.6.0","255.255.255.0");
	pod0_Iface30 = address.Assign(pod0_dev30);
	
	address.SetBase("10.7.0.0","255.255.255.0");
	pod0_Iface31 = address.Assign(pod0_dev31);
	
	address.SetBase("10.7.1.0","255.255.255.0");
	pod0_Iface32 = address.Assign(pod0_dev32);
	

	
	Ipv4InterfaceContainer pod1_Iface,pod1_Iface2,pod1_Iface3,pod1_Iface4,pod1_Iface5,pod1_Iface6,pod1_Iface7,pod1_Iface8,pod1_Iface9,pod1_Iface10,
	pod1_Iface11,pod1_Iface12,pod1_Iface13,pod1_Iface14,pod1_Iface15,pod1_Iface16,pod1_Iface17,pod1_Iface18,pod1_Iface19,pod1_Iface20,pod1_Iface21,
	pod1_Iface22,pod1_Iface23,pod1_Iface24,pod1_Iface25,pod1_Iface26,pod1_Iface27,pod1_Iface28,pod1_Iface29,pod1_Iface30,pod1_Iface31,pod1_Iface32;

	address.SetBase("20.0.0.0","255.255.255.0");
	pod1_Iface = address.Assign (pod1_dev);
	
	address.SetBase("20.0.1.0","255.255.255.0");
	pod1_Iface2 = address.Assign(pod1_dev2);
	
	address.SetBase("20.0.2.0","255.255.255.0");
	pod1_Iface3 = address.Assign(pod1_dev3);
	
	address.SetBase("20.0.3.0","255.255.255.0");
	pod1_Iface4 = address.Assign(pod1_dev4);
	
	address.SetBase("20.1.0.0","255.255.0.0");
	pod1_Iface5 = address.Assign(pod1_dev5);

	address.SetBase("20.2.0.0","255.255.0.0");
	pod1_Iface6 = address.Assign(pod1_dev6);

	address.SetBase("20.1.1.0","255.255.255.0");
	pod1_Iface7 = address.Assign(pod1_dev7);

	address.SetBase("20.2.1.0","255.255.255.0");
	pod1_Iface8 = address.Assign(pod1_dev8);
	
	address.SetBase("20.2.2.0","255.255.255.0");
	pod1_Iface9 = address.Assign(pod1_dev9);
	
	address.SetBase("20.3.2.0","255.255.255.0");
	pod1_Iface10 = address.Assign(pod1_dev10);
	
	address.SetBase("20.3.3.0","255.255.255.0");
	pod1_Iface11 = address.Assign(pod1_dev11);
	
	address.SetBase("20.4.0.0","255.255.255.0");
	pod1_Iface12 = address.Assign(pod1_dev12);
	
	address.SetBase("20.4.1.0","255.255.255.0");
	pod1_Iface13 = address.Assign(pod1_dev13);

	address.SetBase("20.4.2.0","255.255.255.0");
	pod1_Iface14 = address.Assign(pod1_dev14);
	
	address.SetBase("20.4.3.0","255.255.255.0");
	pod1_Iface15 = address.Assign(pod1_dev15);

	address.SetBase("20.4.4.0","255.255.255.0");
	pod1_Iface16 = address.Assign(pod1_dev16);

	address.SetBase("20.5.0.0","255.255.255.0");
	pod1_Iface17 = address.Assign(pod1_dev17);
		
	address.SetBase("20.5.1.0","255.255.255.0");
	pod1_Iface18 = address.Assign(pod1_dev18);
	
	address.SetBase("20.5.2.0","255.255.255.0");
	pod1_Iface19 = address.Assign(pod1_dev19);

	address.SetBase("20.5.3.0","255.255.255.0");
	pod1_Iface20 = address.Assign(pod1_dev20);

	address.SetBase("20.7.2.0","255.255.255.0");
	pod1_Iface21 = address.Assign(pod1_dev21);
	
	address.SetBase("20.5.4.0","255.255.255.0");
	pod1_Iface22 = address.Assign(pod1_dev22);
	
	address.SetBase("20.5.5.0","255.255.255.0");
	pod1_Iface23 = address.Assign(pod1_dev23);
	
	address.SetBase("20.6.0.0","255.255.255.0");
	pod1_Iface24 = address.Assign(pod1_dev24);

	address.SetBase("20.6.1.0","255.255.255.0");
	pod1_Iface25 = address.Assign(pod1_dev25);
	
	address.SetBase("20.6.2.0","255.255.255.0");
	pod1_Iface26 = address.Assign(pod1_dev26);

	address.SetBase("20.6.3.0","255.255.255.0");
	pod1_Iface27 = address.Assign(pod1_dev27);
	
	address.SetBase("20.6.4.0","255.255.255.0");
	pod1_Iface28 = address.Assign(pod1_dev28);

	address.SetBase("20.6.5.0","255.255.255.0");
	pod1_Iface29 = address.Assign(pod1_dev29);
	
	address.SetBase("20.6.6.0","255.255.255.0");
	pod1_Iface30 = address.Assign(pod1_dev30);
	
	address.SetBase("20.7.0.0","255.255.255.0");
	pod1_Iface31 = address.Assign(pod1_dev31);
	
	address.SetBase("20.7.1.0","255.255.255.0");
	pod1_Iface32 = address.Assign(pod1_dev32);
	
	
	Ipv4InterfaceContainer pod2_Iface,pod2_Iface2,pod2_Iface3,pod2_Iface4,pod2_Iface5,pod2_Iface6,pod2_Iface7,pod2_Iface8,pod2_Iface9,pod2_Iface10,pod2_Iface11,
	pod2_Iface12,pod2_Iface13,pod2_Iface14,pod2_Iface15,pod2_Iface16,pod2_Iface17,pod2_Iface18,pod2_Iface19,pod2_Iface20,pod2_Iface21,
	pod2_Iface22,pod2_Iface23,pod2_Iface24,pod2_Iface25,pod2_Iface26,pod2_Iface27,pod2_Iface28,pod2_Iface29,pod2_Iface30,pod2_Iface31,pod2_Iface32;

	address.SetBase("30.0.0.0","255.255.255.0");
	pod2_Iface = address.Assign (pod2_dev);
	
	address.SetBase("30.0.1.0","255.255.255.0");
	pod2_Iface2 = address.Assign(pod2_dev2);
	
	address.SetBase("30.0.2.0","255.255.255.0");
	pod2_Iface3 = address.Assign(pod2_dev3);
	
	address.SetBase("30.0.3.0","255.255.255.0");
	pod2_Iface4 = address.Assign(pod2_dev4);

	address.SetBase("30.1.0.0","255.255.0.0");
	pod2_Iface5 = address.Assign(pod2_dev5);

	address.SetBase("30.2.0.0","255.255.0.0");
	pod2_Iface6 = address.Assign(pod2_dev6);

	address.SetBase("30.1.1.0","255.255.255.0");
	pod2_Iface7 = address.Assign(pod2_dev7);

	address.SetBase("30.2.1.0","255.255.255.0");
	pod2_Iface8 = address.Assign(pod2_dev8);
	
	address.SetBase("30.2.2.0","255.255.255.0");
	pod2_Iface9 = address.Assign(pod2_dev9);
	
	address.SetBase("30.3.2.0","255.255.255.0");
	pod2_Iface10 = address.Assign(pod2_dev10);
	
	address.SetBase("30.3.3.0","255.255.255.0");
	pod2_Iface11 = address.Assign(pod2_dev11);
	
	address.SetBase("30.4.0.0","255.255.255.0");
	pod2_Iface12 = address.Assign(pod2_dev12);
	
	address.SetBase("30.4.1.0","255.255.255.0");
	pod2_Iface13 = address.Assign(pod2_dev13);

	address.SetBase("30.4.2.0","255.255.255.0");
	pod2_Iface14 = address.Assign(pod2_dev14);
	
	address.SetBase("30.4.3.0","255.255.255.0");
	pod2_Iface15 = address.Assign(pod2_dev15);

	address.SetBase("30.4.4.0","255.255.255.0");
	pod2_Iface16 = address.Assign(pod2_dev16);

	address.SetBase("30.5.0.0","255.255.255.0");
	pod2_Iface17 = address.Assign(pod2_dev17);
		
	address.SetBase("30.5.1.0","255.255.255.0");
	pod2_Iface18 = address.Assign(pod2_dev18);
	
	address.SetBase("30.5.2.0","255.255.255.0");
	pod2_Iface19 = address.Assign(pod2_dev19);

	address.SetBase("30.5.3.0","255.255.255.0");
	pod2_Iface20 = address.Assign(pod2_dev20);
	
	address.SetBase("30.7.2.0","255.255.255.0");
	pod2_Iface21 = address.Assign(pod2_dev21);
	
	address.SetBase("30.5.4.0","255.255.255.0");
	pod2_Iface22 = address.Assign(pod2_dev22);
	
	address.SetBase("30.5.5.0","255.255.255.0");
	pod2_Iface23 = address.Assign(pod2_dev23);
	
	address.SetBase("30.6.0.0","255.255.255.0");
	pod2_Iface24 = address.Assign(pod2_dev24);

	address.SetBase("30.6.1.0","255.255.255.0");
	pod2_Iface25 = address.Assign(pod2_dev25);
	
	address.SetBase("30.6.2.0","255.255.255.0");
	pod2_Iface26 = address.Assign(pod2_dev26);

	address.SetBase("30.6.3.0","255.255.255.0");
	pod2_Iface27 = address.Assign(pod2_dev27);
	
	address.SetBase("30.6.4.0","255.255.255.0");
	pod2_Iface28 = address.Assign(pod2_dev28);
	
	address.SetBase("30.6.5.0","255.255.255.0");
	pod2_Iface29 = address.Assign(pod2_dev29);
	
	address.SetBase("30.6.6.0","255.255.255.0");
	pod2_Iface30 = address.Assign(pod2_dev30);
	
	address.SetBase("30.7.0.0","255.255.255.0");
	pod2_Iface31 = address.Assign(pod2_dev31);
	
	address.SetBase("30.7.1.0","255.255.255.0");
	pod2_Iface32 = address.Assign(pod2_dev32);
	
	
	Ipv4InterfaceContainer pod3_Iface,pod3_Iface2,pod3_Iface3,pod3_Iface4,pod3_Iface5,pod3_Iface6,pod3_Iface7,pod3_Iface8,pod3_Iface9,pod3_Iface10,pod3_Iface11,
	pod3_Iface12,pod3_Iface13,pod3_Iface14,pod3_Iface15,pod3_Iface16,pod3_Iface17,pod3_Iface18,pod3_Iface19,pod3_Iface20,pod3_Iface21,
	pod3_Iface22,pod3_Iface23,pod3_Iface24,pod3_Iface25,pod3_Iface26,pod3_Iface27,pod3_Iface28,pod3_Iface29,pod3_Iface30,pod3_Iface31,pod3_Iface32;
			
	address.SetBase("40.0.0.0","255.255.255.0");
	pod3_Iface = address.Assign (pod3_dev);
	
	address.SetBase("40.0.1.0","255.255.255.0");
	pod3_Iface2 = address.Assign(pod3_dev2);
	
	address.SetBase("40.0.2.0","255.255.255.0");
	pod3_Iface3 = address.Assign(pod3_dev3);
	
	address.SetBase("40.0.3.0","255.255.255.0");
	pod3_Iface4 = address.Assign(pod3_dev4);
	
	address.SetBase("40.1.0.0","255.255.0.0");
	pod3_Iface5 = address.Assign(pod3_dev5);

	address.SetBase("40.2.0.0","255.255.0.0");
	pod3_Iface6 = address.Assign(pod3_dev6);

	address.SetBase("40.1.1.0","255.255.255.0");
	pod3_Iface7 = address.Assign(pod3_dev7);

	address.SetBase("40.2.1.0","255.255.255.0");
	pod3_Iface8 = address.Assign(pod3_dev8);
	
	address.SetBase("40.2.2.0","255.255.255.0");
	pod3_Iface9 = address.Assign(pod3_dev9);
	
	address.SetBase("40.3.2.0","255.255.255.0");
	pod3_Iface10 = address.Assign(pod3_dev10);
	
	address.SetBase("40.3.3.0","255.255.255.0");
	pod3_Iface11 = address.Assign(pod3_dev11);
	
	address.SetBase("40.4.0.0","255.255.255.0");
	pod3_Iface12 = address.Assign(pod3_dev12);
	
	address.SetBase("40.4.1.0","255.255.255.0");
	pod3_Iface13 = address.Assign(pod3_dev13);

	address.SetBase("40.4.2.0","255.255.255.0");
	pod3_Iface14 = address.Assign(pod3_dev14);
	
	address.SetBase("40.4.3.0","255.255.255.0");
	pod3_Iface15 = address.Assign(pod3_dev15);

	address.SetBase("40.4.4.0","255.255.255.0");
	pod3_Iface16 = address.Assign(pod3_dev16);

	address.SetBase("40.5.0.0","255.255.255.0");
	pod3_Iface17 = address.Assign(pod3_dev17);
		
	address.SetBase("40.5.1.0","255.255.255.0");
	pod3_Iface18 = address.Assign(pod3_dev18);
	
	address.SetBase("40.5.2.0","255.255.255.0");
	pod3_Iface19 = address.Assign(pod3_dev19);

	address.SetBase("40.5.3.0","255.255.255.0");
	pod3_Iface20 = address.Assign(pod3_dev20);
	
	address.SetBase("40.7.2.0","255.255.255.0");
	pod3_Iface21 = address.Assign(pod3_dev21);
	
	address.SetBase("40.5.4.0","255.255.255.0");
	pod3_Iface22 = address.Assign(pod3_dev22);
	
	address.SetBase("40.5.5.0","255.255.255.0");
	pod3_Iface23 = address.Assign(pod3_dev23);
	
	address.SetBase("40.6.0.0","255.255.255.0");
	pod3_Iface24 = address.Assign(pod3_dev24);
	
	address.SetBase("40.6.1.0","255.255.255.0");
	pod3_Iface25 = address.Assign(pod3_dev25);
	
	address.SetBase("40.6.2.0","255.255.255.0");
	pod3_Iface26 = address.Assign(pod3_dev26);
	
	address.SetBase("40.6.3.0","255.255.255.0");
	pod3_Iface27 = address.Assign(pod3_dev27);
	
	address.SetBase("40.6.4.0","255.255.255.0");
	pod3_Iface28 = address.Assign(pod3_dev28);
	
	address.SetBase("40.6.5.0","255.255.255.0");
	pod3_Iface29 = address.Assign(pod3_dev29);
	
	address.SetBase("40.6.6.0","255.255.255.0");
	pod3_Iface30 = address.Assign(pod3_dev30);
	
	address.SetBase("40.7.0.0","255.255.255.0");
	pod3_Iface31 = address.Assign(pod3_dev31);
	
	address.SetBase("40.7.1.0","255.255.255.0");
	pod3_Iface32 = address.Assign(pod3_dev32);
	
	Ipv4InterfaceContainer SW4_Connection,SW4_Connection2,SW4_Connection3,SW4_Connection4,SW4_Connection5,SW4_Connection6,SW4_Connection7,
	SW4_Connection8;
	
	address.SetBase("60.0.0.0","255.255.255.0");
	SW4_Connection = address.Assign (sw4_dev);
	
	address.SetBase("60.0.1.0","255.255.255.0");
	SW4_Connection2 = address.Assign (sw4_dev2);
	
	address.SetBase("60.0.2.0","255.255.255.0");
	SW4_Connection3 = address.Assign (sw4_dev3);
	
	address.SetBase("60.0.3.0","255.255.255.0");
	SW4_Connection4 = address.Assign (sw4_dev4);
	
	address.SetBase("60.1.0.0","255.255.255.0");
	SW4_Connection5 = address.Assign (sw4_dev5);
	
	address.SetBase("60.2.0.0","255.255.255.0");
	SW4_Connection6 = address.Assign (sw4_dev6);
	
	address.SetBase("60.1.1.0","255.255.255.0");
	SW4_Connection7 = address.Assign (sw4_dev7);
	
	address.SetBase("60.2.1.0","255.255.255.0");
	SW4_Connection8 = address.Assign (sw4_dev8);
	
	Ipv4InterfaceContainer SW5_Connection,SW5_Connection2,SW5_Connection3,SW5_Connection4,SW5_Connection5,SW5_Connection6,SW5_Connection7,
	SW5_Connection8;
	
	address.SetBase("70.0.0.0","255.255.255.0");
	SW5_Connection = address.Assign (sw5_dev);
	
	address.SetBase("70.0.1.0","255.255.255.0");
	SW5_Connection2 = address.Assign (sw5_dev2);
	
	address.SetBase("70.0.2.0","255.255.255.0");
	SW5_Connection3 = address.Assign (sw5_dev3);
	
	address.SetBase("70.0.3.0","255.255.255.0");
	SW5_Connection4 = address.Assign (sw5_dev4);
	
	address.SetBase("70.1.0.0","255.255.255.0");
	SW5_Connection5 = address.Assign (sw5_dev5);
	
	address.SetBase("70.2.0.0","255.255.255.0");
	SW5_Connection6 = address.Assign (sw5_dev6);
	
	address.SetBase("70.1.1.0","255.255.255.0");
	SW5_Connection7 = address.Assign (sw5_dev7);
	
	address.SetBase("70.2.1.0","255.255.255.0");
	SW5_Connection8 = address.Assign (sw5_dev8);
	
	Ipv4InterfaceContainer SW6_Connection,SW6_Connection2,SW6_Connection3,SW6_Connection4,SW6_Connection5,SW6_Connection6,SW6_Connection7,
	SW6_Connection8;
	
	address.SetBase("80.0.0.0","255.255.255.0");
	SW6_Connection = address.Assign (sw6_dev);
	
	address.SetBase("80.0.1.0","255.255.255.0");
	SW6_Connection2 = address.Assign (sw6_dev2);
	
	address.SetBase("80.0.2.0","255.255.255.0");
	SW6_Connection3 = address.Assign (sw6_dev3);
	
	address.SetBase("80.0.3.0","255.255.255.0");
	SW6_Connection4 = address.Assign (sw6_dev4);
	
	address.SetBase("80.1.0.0","255.255.255.0");
	SW6_Connection5 = address.Assign (sw6_dev5);
	
	address.SetBase("80.2.0.0","255.255.255.0");
	SW6_Connection6 = address.Assign (sw6_dev6);
	
	address.SetBase("80.1.1.0","255.255.255.0");
	SW6_Connection7 = address.Assign (sw6_dev7);
	
	address.SetBase("80.2.1.0","255.255.255.0");
	SW6_Connection8 = address.Assign (sw6_dev8);
	
	Ipv4InterfaceContainer SW7_Connection,SW7_Connection2,SW7_Connection3,SW7_Connection4,SW7_Connection5,SW7_Connection6,SW7_Connection7,
	SW7_Connection8;
	
	address.SetBase("90.0.0.0","255.255.255.0");
	SW7_Connection = address.Assign (sw7_dev);
	
	address.SetBase("90.0.1.0","255.255.255.0");
	SW7_Connection2 = address.Assign (sw7_dev2);
	
	address.SetBase("90.0.2.0","255.255.255.0");
	SW7_Connection3 = address.Assign (sw7_dev3);
	
	address.SetBase("90.0.3.0","255.255.255.0");
	SW7_Connection4 = address.Assign (sw7_dev4);
	
	address.SetBase("90.1.0.0","255.255.255.0");
	SW7_Connection5 = address.Assign (sw7_dev5);
	
	address.SetBase("90.2.0.0","255.255.255.0");
	SW7_Connection6 = address.Assign (sw7_dev6);
	
	address.SetBase("90.1.1.0","255.255.255.0");
	SW7_Connection7 = address.Assign (sw7_dev7);
	
	address.SetBase("90.2.1.0","255.255.255.0");
	SW7_Connection8 = address.Assign (sw7_dev8);
	
	
	//Core router Ifaces
	Ipv4InterfaceContainer core_Iface,core_Iface2,core_Iface3,core_Iface4,core_Iface5,core_Iface6,core_Iface7,core_Iface8;
	Ipv4InterfaceContainer core_Iface9,core_Iface10,core_Iface11,core_Iface12,core_Iface13,core_Iface14,core_Iface15,core_Iface16;
	
	address.SetBase("50.0.1.0","255.255.255.0");
	core_Iface = address.Assign(core_dev1);

	address.SetBase("50.1.2.0","255.255.255.0");
	core_Iface2 = address.Assign(core_dev2);

	address.SetBase("50.1.3.0","255.255.255.0");
	core_Iface3 = address.Assign(core_dev3);

	address.SetBase("50.1.4.0","255.255.255.0");
	core_Iface4 = address.Assign(core_dev4);
	
	address.SetBase("50.2.1.0","255.255.255.0");
	core_Iface5 = address.Assign(core_dev5);

	address.SetBase("50.2.2.0","255.255.255.0");
	core_Iface6 = address.Assign(core_dev6);

	address.SetBase("50.2.3.0","255.255.255.0");
	core_Iface7 = address.Assign(core_dev7);

	address.SetBase("50.2.4.0","255.255.255.0");
	core_Iface8 = address.Assign(core_dev8);
	
	address.SetBase("50.3.1.0","255.255.255.0");
	core_Iface9 = address.Assign(core_dev9);
	
	address.SetBase("50.3.2.0","255.255.255.0");
	core_Iface10 = address.Assign(core_dev10);
	
	address.SetBase("50.3.3.0","255.255.255.0");
	core_Iface11 = address.Assign(core_dev11);
	
	address.SetBase("50.3.4.0","255.255.255.0");
	core_Iface12 = address.Assign(core_dev12);
	
	address.SetBase("50.4.1.0","255.255.255.0");
	core_Iface13 = address.Assign(core_dev13);
	
	address.SetBase("50.4.2.0","255.255.255.0");
	core_Iface14 = address.Assign(core_dev14);
	
	address.SetBase("50.4.3.0","255.255.255.0");
	core_Iface15 = address.Assign(core_dev15);
	
	address.SetBase("50.4.4.0","255.255.255.0");
	core_Iface16 = address.Assign(core_dev16);
	
	
	


	/*Ipv4InterfaceContainer Array[8];

	Array[0] = pod0_Iface21;
	Array[1] = pod0_Iface22;
	Array[2] = pod1_Iface21;
	Array[3] = pod1_Iface22;
	Array[4] = pod2_Iface21;
	Array[5] = pod2_Iface22;
	Array[6] = pod3_Iface21;
	Array[7] = pod3_Iface22;
	Array[8] = pod0_Iface23;
	Array[9] = pod0_Iface24;
	Array[10] = pod1_Iface23;
	Array[11] = pod1_Iface24;
	Array[12] = pod2_Iface23;
	Array[13] = pod2_Iface24;
	Array[14] = pod3_Iface23;
	Array[15] = pod3_Iface24;
	Array[16] = pod0_Iface25;
	Array[17] = pod0_Iface26;
	Array[18] = pod1_Iface25;
	Array[19] = pod1_Iface26;
	Array[20] = pod2_Iface25;
	Array[21] = pod2_Iface26;
	Array[22] = pod3_Iface25;
	Array[23] = pod3_Iface26;
	Array[24] = pod0_Iface27;
	Array[25] = pod0_Iface28;
	Array[26] = pod1_Iface27;
	Array[27] = pod1_Iface28;
	Array[28] = pod2_Iface27;
	Array[29] = pod2_Iface28;
	Array[30] = pod3_Iface27;
	Array[31] = pod3_Iface28;*/
	

	/*for(int i=0;i<8;i++)
	{
		std::pair<Ptr<Ipv4>, uint32_t> returnValue = Array[i].Get(0);
    		Ptr<Ipv4> ipv4 = returnValue.first;
    		uint32_t index = returnValue.second;
    		Ptr<Ipv4Interface> iface = ipv4->GetObject<Ipv4L3Protocol> ()->GetInterface(index);
    		iface->SetDown();
	}*/
	
	Config::SetDefault ("ns3::Ipv4GlobalRouting::RespondToInterfaceEvents", BooleanValue (true));
	
	double InterArrival[97];
	int j=0;
	InterArrival[j+1] = 0;
	
	srand(time(NULL));
	
	for(j=1;j<=97;j++)
	{
		InterArrival[j] = GenerateRandInterval(0.095);
	}
	
	for(j=1;j<=97;j++)
	{
		InterArrival[j+1] += InterArrival[j];
		cout<<j<<"-"<<"InterArrivalTime = "<<InterArrival[j]<<"\n";
	}

	//Routing tables
	Ipv4GlobalRoutingHelper:: PopulateRoutingTables();
	
	
	/*Ptr<Ipv4> A4 = A->GetObject<Ipv4> ();
 	Ipv4Address ipAddr = A4->GetAddress (1,0).GetLocal ();
	cout<<"Client1`s address = "<<ipAddr<<"\n";*/

	//Applications
	
	cout<<"Time for Servers"<<"\n";	
	srand(time(NULL));

	UdpEchoServerHelper EchoServer (9);
	ApplicationContainer serverApps,serverApps3,serverApps5,serverApps7,serverApps9,serverApps11;
	serverApps = EchoServer.Install (pod0.Get (0));
	serverApps3 = EchoServer.Install (pod0.Get (1));
	serverApps5 = EchoServer.Install (pod0.Get (2));
	serverApps7 = EchoServer.Install (pod0.Get (3));
	serverApps9 = EchoServer.Install (pod0.Get (4));
	serverApps11 = EchoServer.Install (pod0.Get (5));
	serverApps.Start (Seconds (GenerateRandReply(0.005)));
	serverApps.Stop (Seconds (10.0));
	serverApps3.Start (Seconds (GenerateRandReply(0.005)));
	serverApps3.Stop (Seconds (10.0));
	serverApps5.Start (Seconds (GenerateRandReply(0.005)));
	serverApps5.Stop (Seconds (10.0));
	serverApps7.Start (Seconds (GenerateRandReply(0.005)));
	serverApps7.Stop (Seconds (10.0));
	serverApps9.Start (Seconds (GenerateRandReply(0.005)));
	serverApps9.Stop (Seconds (10.0));
	serverApps11.Start (Seconds (GenerateRandReply(0.005)));
	serverApps11.Stop (Seconds (10.0));

	
	UdpEchoServerHelper EchoServer1 (9);
	ApplicationContainer serverApps13,serverApps15,serverApps17,serverApps19,serverApps21,serverApps23;
	serverApps13 = EchoServer1.Install (pod1.Get (0));
	serverApps15 = EchoServer1.Install (pod1.Get (1));
	serverApps17 = EchoServer1.Install (pod1.Get (2));
	serverApps19 = EchoServer1.Install (pod1.Get (3));
	serverApps21 = EchoServer1.Install (pod1.Get (4));
	serverApps23 = EchoServer1.Install (pod1.Get (5));
	serverApps13.Start (Seconds (GenerateRandReply(0.005)));
	serverApps13.Stop (Seconds (10.0));
	serverApps15.Start (Seconds (GenerateRandReply(0.005)));
	serverApps15.Stop (Seconds (10.0));
	serverApps17.Start (Seconds (GenerateRandReply(0.005)));
	serverApps17.Stop (Seconds (10.0));
	serverApps19.Start (Seconds (GenerateRandReply(0.005)));
	serverApps19.Stop (Seconds (10.0));
	serverApps21.Start (Seconds (GenerateRandReply(0.005)));
	serverApps21.Stop (Seconds (10.0));
	serverApps23.Start (Seconds (GenerateRandReply(0.005)));
	serverApps23.Stop (Seconds (10.0));
	

	UdpEchoServerHelper EchoServer2 (9);
	ApplicationContainer serverApps25,serverApps27,serverApps29,serverApps31,serverApps33,serverApps35;
	serverApps25 = EchoServer2.Install (pod2.Get (0));
	serverApps27 = EchoServer2.Install (pod2.Get (1));
	serverApps29 = EchoServer2.Install (pod2.Get (2));
	serverApps31 = EchoServer2.Install (pod2.Get (3));
	serverApps33 = EchoServer2.Install (pod2.Get (4));
	serverApps35 = EchoServer2.Install (pod2.Get (5));
	serverApps25.Start (Seconds (GenerateRandReply(0.005)));
	serverApps25.Stop (Seconds (10.0));
	serverApps27.Start (Seconds (GenerateRandReply(0.005)));
	serverApps27.Stop (Seconds (10.0));
	serverApps29.Start (Seconds (GenerateRandReply(0.005)));
	serverApps29.Stop (Seconds (10.0));
	serverApps31.Start (Seconds (GenerateRandReply(0.005)));
	serverApps31.Stop (Seconds (10.0));
	serverApps33.Start (Seconds (GenerateRandReply(0.005)));
	serverApps33.Stop (Seconds (10.0));
	serverApps35.Start (Seconds (GenerateRandReply(0.005)));
	serverApps35.Stop (Seconds (10.0));

	
	UdpEchoServerHelper EchoServer3 (9);
	ApplicationContainer serverApps37,serverApps39,serverApps41,serverApps43,serverApps45,serverApps47;
	serverApps37 = EchoServer3.Install (pod3.Get (0));
	serverApps39 = EchoServer3.Install (pod3.Get (1));
	serverApps41 = EchoServer3.Install (pod3.Get (2));
	serverApps43 = EchoServer3.Install (pod3.Get (3));
	serverApps45 = EchoServer3.Install (pod3.Get (4));
	serverApps47 = EchoServer3.Install (pod3.Get (5));
	serverApps37.Start (Seconds (GenerateRandReply(0.005)));
	serverApps37.Stop (Seconds (10.0));
	serverApps39.Start (Seconds (GenerateRandReply(0.005)));
	serverApps39.Stop (Seconds (10.0));
	serverApps41.Start (Seconds (GenerateRandReply(0.005)));
	serverApps41.Stop (Seconds (10.0));
	serverApps43.Start (Seconds (GenerateRandReply(0.005)));
	serverApps43.Stop (Seconds (10.0));
	serverApps45.Start (Seconds (GenerateRandReply(0.005)));
	serverApps45.Stop (Seconds (10.0));
	serverApps47.Start (Seconds (GenerateRandReply(0.005)));
	serverApps47.Stop (Seconds (10.0));



	UdpEchoClientHelper EchoClient (pod0_Iface21.GetAddress (0), 9);
	EchoClient.SetAttribute ("MaxPackets", UintegerValue (200000));
	EchoClient.SetAttribute ("Interval", TimeValue (Seconds (InterArrival[1])));
	EchoClient.SetAttribute ("PacketSize", UintegerValue (GenerateRandText(1000)));
	
	UdpEchoClientHelper EchoClient2 (pod0_Iface22.GetAddress (0), 9);
	EchoClient2.SetAttribute ("MaxPackets", UintegerValue (200000));
	EchoClient2.SetAttribute ("Interval", TimeValue (Seconds (InterArrival[2])));
	EchoClient2.SetAttribute ("PacketSize", UintegerValue (GenerateRandText(1000)));
	
	UdpEchoClientHelper EchoClient3 (pod0_Iface23.GetAddress (0), 9);
	EchoClient3.SetAttribute ("MaxPackets", UintegerValue (200000));
	EchoClient3.SetAttribute ("Interval", TimeValue (Seconds (InterArrival[3])));
	EchoClient3.SetAttribute ("PacketSize", UintegerValue (GenerateRandText(1000)));
	
	UdpEchoClientHelper EchoClient4 (pod0_Iface24.GetAddress (0), 9);
	EchoClient4.SetAttribute ("MaxPackets", UintegerValue (200000));
	EchoClient4.SetAttribute ("Interval", TimeValue (Seconds (InterArrival[4])));
	EchoClient4.SetAttribute ("PacketSize", UintegerValue (GenerateRandText(1000)));
	
	UdpEchoClientHelper EchoClient5 (pod0_Iface25.GetAddress (0), 9);
	EchoClient5.SetAttribute ("MaxPackets", UintegerValue (200000));
	EchoClient5.SetAttribute ("Interval", TimeValue (Seconds (InterArrival[5])));
	EchoClient5.SetAttribute ("PacketSize", UintegerValue (GenerateRandText(1000)));
	
	UdpEchoClientHelper EchoClient6 (pod0_Iface26.GetAddress (0), 9);
	EchoClient6 .SetAttribute ("MaxPackets", UintegerValue (200000));
	EchoClient6 .SetAttribute ("Interval", TimeValue (Seconds (InterArrival[6])));
	EchoClient6 .SetAttribute ("PacketSize", UintegerValue (GenerateRandText(1000)));
	
	UdpEchoClientHelper EchoClient7 (pod0_Iface27.GetAddress (0), 9);
	EchoClient7.SetAttribute ("MaxPackets", UintegerValue (200000));
	EchoClient7.SetAttribute ("Interval", TimeValue (Seconds (InterArrival[7])));
	EchoClient7.SetAttribute ("PacketSize", UintegerValue (GenerateRandText(1000)));
	
	UdpEchoClientHelper EchoClient8 (pod0_Iface28.GetAddress (0), 9);
	EchoClient8.SetAttribute ("MaxPackets", UintegerValue (200000));
	EchoClient8.SetAttribute ("Interval", TimeValue (Seconds (InterArrival[8])));
	EchoClient8.SetAttribute ("PacketSize", UintegerValue (GenerateRandText(1000)));
	
	UdpEchoClientHelper EchoClient9 (pod0_Iface29.GetAddress (0), 9);
	EchoClient9.SetAttribute ("MaxPackets", UintegerValue (200000));
	EchoClient9.SetAttribute ("Interval", TimeValue (Seconds (InterArrival[9])));
	EchoClient9.SetAttribute ("PacketSize", UintegerValue (GenerateRandText(1000)));
	
	UdpEchoClientHelper EchoClient10 (pod0_Iface30.GetAddress (0), 9);
	EchoClient10.SetAttribute ("MaxPackets", UintegerValue (200000));
	EchoClient10.SetAttribute ("Interval", TimeValue (Seconds (InterArrival[10])));
	EchoClient10.SetAttribute ("PacketSize", UintegerValue (GenerateRandText(1000)));
	
	UdpEchoClientHelper EchoClient11 (pod0_Iface31.GetAddress (0), 9);
	EchoClient11.SetAttribute ("MaxPackets", UintegerValue (200000));
	EchoClient11.SetAttribute ("Interval", TimeValue (Seconds (InterArrival[11])));
	EchoClient11.SetAttribute ("PacketSize", UintegerValue (GenerateRandText(1000)));
	
	UdpEchoClientHelper EchoClient12 (pod0_Iface32.GetAddress (0), 9);
	EchoClient12.SetAttribute ("MaxPackets", UintegerValue (200000));
	EchoClient12.SetAttribute ("Interval", TimeValue (Seconds (InterArrival[12])));
	EchoClient12.SetAttribute ("PacketSize", UintegerValue (GenerateRandText(1000)));
	
	UdpEchoClientHelper EchoClient13 (pod1_Iface21.GetAddress (0), 9);
	EchoClient13.SetAttribute ("MaxPackets", UintegerValue (200000));
	EchoClient13.SetAttribute ("Interval", TimeValue (Seconds (InterArrival[13])));
	EchoClient13.SetAttribute ("PacketSize", UintegerValue (GenerateRandText(1000)));
	
	UdpEchoClientHelper EchoClient14 (pod1_Iface22.GetAddress (0), 9);
	EchoClient14.SetAttribute ("MaxPackets", UintegerValue (200000));
	EchoClient14.SetAttribute ("Interval", TimeValue (Seconds (InterArrival[14])));
	EchoClient14.SetAttribute ("PacketSize", UintegerValue (GenerateRandText(1000)));
	
	UdpEchoClientHelper EchoClient15 (pod1_Iface23.GetAddress (0), 9);
	EchoClient15.SetAttribute ("MaxPackets", UintegerValue (200000));
	EchoClient15.SetAttribute ("Interval", TimeValue (Seconds (InterArrival[15])));
	EchoClient15.SetAttribute ("PacketSize", UintegerValue (GenerateRandText(1000)));
	
	UdpEchoClientHelper EchoClient16 (pod1_Iface24.GetAddress (0), 9);
	EchoClient16.SetAttribute ("MaxPackets", UintegerValue (200000));
	EchoClient16.SetAttribute ("Interval", TimeValue (Seconds (InterArrival[16])));
	EchoClient16.SetAttribute ("PacketSize", UintegerValue (GenerateRandText(1000)));

	UdpEchoClientHelper EchoClient17 (pod1_Iface25.GetAddress (0), 9);
	EchoClient17.SetAttribute ("MaxPackets", UintegerValue (200000));
	EchoClient17.SetAttribute ("Interval", TimeValue (Seconds (InterArrival[17])));
	EchoClient17.SetAttribute ("PacketSize", UintegerValue (GenerateRandText(1000)));

	UdpEchoClientHelper EchoClient18 (pod1_Iface26.GetAddress (0), 9);
	EchoClient18.SetAttribute ("MaxPackets", UintegerValue (200000));
	EchoClient18.SetAttribute ("Interval", TimeValue (Seconds (InterArrival[18])));
	EchoClient18.SetAttribute ("PacketSize", UintegerValue (GenerateRandText(1000)));
	
	UdpEchoClientHelper EchoClient19 (pod1_Iface27.GetAddress (0), 9);
	EchoClient19.SetAttribute ("MaxPackets", UintegerValue (200000));
	EchoClient19.SetAttribute ("Interval", TimeValue (Seconds (InterArrival[19])));
	EchoClient19.SetAttribute ("PacketSize", UintegerValue (GenerateRandText(1000)));
	
	UdpEchoClientHelper EchoClient20 (pod1_Iface28.GetAddress (0), 9);
	EchoClient20.SetAttribute ("MaxPackets", UintegerValue (200000));
	EchoClient20.SetAttribute ("Interval", TimeValue (Seconds (InterArrival[20])));
	EchoClient20.SetAttribute ("PacketSize", UintegerValue (GenerateRandText(1000)));
	
	UdpEchoClientHelper EchoClient21 (pod1_Iface29.GetAddress (0), 9);
	EchoClient21.SetAttribute ("MaxPackets", UintegerValue (200000));
	EchoClient21.SetAttribute ("Interval", TimeValue (Seconds (InterArrival[21])));
	EchoClient21.SetAttribute ("PacketSize", UintegerValue (GenerateRandText(1000)));

	UdpEchoClientHelper EchoClient22 (pod1_Iface30.GetAddress (0), 9);
	EchoClient22.SetAttribute ("MaxPackets", UintegerValue (200000));
	EchoClient22.SetAttribute ("Interval", TimeValue (Seconds (InterArrival[23])));
	EchoClient22.SetAttribute ("PacketSize", UintegerValue (GenerateRandText(1000)));

	UdpEchoClientHelper EchoClient23 (pod1_Iface31.GetAddress (0), 9);
	EchoClient23.SetAttribute ("MaxPackets", UintegerValue (200000));
	EchoClient23.SetAttribute ("Interval", TimeValue (Seconds (InterArrival[24])));
	EchoClient23.SetAttribute ("PacketSize", UintegerValue (GenerateRandText(1000)));

	UdpEchoClientHelper EchoClient24 (pod1_Iface32.GetAddress (0), 9);
	EchoClient24.SetAttribute ("MaxPackets", UintegerValue (200000));
	EchoClient24.SetAttribute ("Interval", TimeValue (Seconds (InterArrival[25])));
	EchoClient24.SetAttribute ("PacketSize", UintegerValue (GenerateRandText(1000)));
	
	UdpEchoClientHelper EchoClient25 (pod2_Iface21.GetAddress (0), 9);
	EchoClient25.SetAttribute ("MaxPackets", UintegerValue (200000));
	EchoClient25.SetAttribute ("Interval", TimeValue (Seconds (InterArrival[26])));
	EchoClient25.SetAttribute ("PacketSize", UintegerValue (GenerateRandText(1000)));
	
	UdpEchoClientHelper EchoClient26 (pod2_Iface22.GetAddress (0), 9);
	EchoClient26.SetAttribute ("MaxPackets", UintegerValue (200000));
	EchoClient26.SetAttribute ("Interval", TimeValue (Seconds (InterArrival[27])));
	EchoClient26.SetAttribute ("PacketSize", UintegerValue (GenerateRandText(1000)));
	
	UdpEchoClientHelper EchoClient27 (pod2_Iface23.GetAddress (0), 9);
	EchoClient27.SetAttribute ("MaxPackets", UintegerValue (200000));
	EchoClient27.SetAttribute ("Interval", TimeValue (Seconds (InterArrival[28])));
	EchoClient27.SetAttribute ("PacketSize", UintegerValue (GenerateRandText(1000)));
	
	UdpEchoClientHelper EchoClient28 (pod2_Iface24.GetAddress (0), 9);
	EchoClient28.SetAttribute ("MaxPackets", UintegerValue (200000));
	EchoClient28.SetAttribute ("Interval", TimeValue (Seconds (InterArrival[29])));
	EchoClient28.SetAttribute ("PacketSize", UintegerValue (GenerateRandText(1000)));
	
	UdpEchoClientHelper EchoClient29 (pod2_Iface25.GetAddress (0), 9);
	EchoClient29.SetAttribute ("MaxPackets", UintegerValue (200000));
	EchoClient29.SetAttribute ("Interval", TimeValue (Seconds (InterArrival[30])));
	EchoClient29.SetAttribute ("PacketSize", UintegerValue (GenerateRandText(1000)));
	
	UdpEchoClientHelper EchoClient30 (pod2_Iface26.GetAddress (0), 9);
	EchoClient30.SetAttribute ("MaxPackets", UintegerValue (200000));
	EchoClient30.SetAttribute ("Interval", TimeValue (Seconds (InterArrival[31])));
	EchoClient30.SetAttribute ("PacketSize", UintegerValue (GenerateRandText(1000)));
	
	UdpEchoClientHelper EchoClient31 (pod2_Iface27.GetAddress (0), 9);
	EchoClient31.SetAttribute ("MaxPackets", UintegerValue (200000));
	EchoClient31.SetAttribute ("Interval", TimeValue (Seconds (InterArrival[32])));
	EchoClient31.SetAttribute ("PacketSize", UintegerValue (GenerateRandText(1000)));
	
	UdpEchoClientHelper EchoClient32 (pod2_Iface28.GetAddress (0), 9);
	EchoClient32.SetAttribute ("MaxPackets", UintegerValue (200000));
	EchoClient32.SetAttribute ("Interval", TimeValue (Seconds (InterArrival[33])));
	EchoClient32.SetAttribute ("PacketSize", UintegerValue (GenerateRandText(1000)));
	
	UdpEchoClientHelper EchoClient33 (pod2_Iface29.GetAddress (0), 9);
	EchoClient33.SetAttribute ("MaxPackets", UintegerValue (200000));
	EchoClient33.SetAttribute ("Interval", TimeValue (Seconds (InterArrival[34])));
	EchoClient33.SetAttribute ("PacketSize", UintegerValue (GenerateRandText(1000)));
	
	UdpEchoClientHelper EchoClient34 (pod2_Iface30.GetAddress (0), 9);
	EchoClient34.SetAttribute ("MaxPackets", UintegerValue (200000));
	EchoClient34.SetAttribute ("Interval", TimeValue (Seconds (InterArrival[35])));
	EchoClient34.SetAttribute ("PacketSize", UintegerValue (GenerateRandText(1000)));
	
	UdpEchoClientHelper EchoClient35 (pod2_Iface31.GetAddress (0), 9);
	EchoClient35.SetAttribute ("MaxPackets", UintegerValue (200000));
	EchoClient35.SetAttribute ("Interval", TimeValue (Seconds (InterArrival[36])));
	EchoClient35.SetAttribute ("PacketSize", UintegerValue (GenerateRandText(1000)));
	
	UdpEchoClientHelper EchoClient36 (pod2_Iface32.GetAddress (0), 9);
	EchoClient36.SetAttribute ("MaxPackets", UintegerValue (200000));
	EchoClient36.SetAttribute ("Interval", TimeValue (Seconds (InterArrival[37])));
	EchoClient36.SetAttribute ("PacketSize", UintegerValue (GenerateRandText(1000)));
	
	UdpEchoClientHelper EchoClient37 (pod3_Iface21.GetAddress (0), 9);
	EchoClient37.SetAttribute ("MaxPackets", UintegerValue (200000));
	EchoClient37.SetAttribute ("Interval", TimeValue (Seconds (InterArrival[38])));
	EchoClient37.SetAttribute ("PacketSize", UintegerValue (GenerateRandText(1000)));
	
	UdpEchoClientHelper EchoClient38 (pod3_Iface22.GetAddress (0), 9);
	EchoClient38.SetAttribute ("MaxPackets", UintegerValue (200000));
	EchoClient38.SetAttribute ("Interval", TimeValue (Seconds (InterArrival[39])));
	EchoClient38.SetAttribute ("PacketSize", UintegerValue (GenerateRandText(1000)));
	
	UdpEchoClientHelper EchoClient40 (pod3_Iface23.GetAddress (0), 9);
	EchoClient40.SetAttribute ("MaxPackets", UintegerValue (200000));
	EchoClient40.SetAttribute ("Interval", TimeValue (Seconds (InterArrival[40])));
	EchoClient40.SetAttribute ("PacketSize", UintegerValue (GenerateRandText(1000)));
	
	UdpEchoClientHelper EchoClient41 (pod3_Iface24.GetAddress (0), 9);
	EchoClient41.SetAttribute ("MaxPackets", UintegerValue (200000));
	EchoClient41.SetAttribute ("Interval", TimeValue (Seconds (InterArrival[41])));
	EchoClient41.SetAttribute ("PacketSize", UintegerValue (GenerateRandText(1000)));

	UdpEchoClientHelper EchoClient42 (pod3_Iface25.GetAddress (0), 9);
	EchoClient42.SetAttribute ("MaxPackets", UintegerValue (200000));
	EchoClient42.SetAttribute ("Interval", TimeValue (Seconds (InterArrival[42])));
	EchoClient42.SetAttribute ("PacketSize", UintegerValue (GenerateRandText(1000)));
			
	UdpEchoClientHelper EchoClient43 (pod3_Iface26.GetAddress (0), 9);
	EchoClient43.SetAttribute ("MaxPackets", UintegerValue (200000));
	EchoClient43.SetAttribute ("Interval", TimeValue (Seconds (InterArrival[43])));
	EchoClient43.SetAttribute ("PacketSize", UintegerValue (GenerateRandText(1000)));

	UdpEchoClientHelper EchoClient44 (pod3_Iface27.GetAddress (0), 9);
	EchoClient44.SetAttribute ("MaxPackets", UintegerValue (200000));
	EchoClient44.SetAttribute ("Interval", TimeValue (Seconds (InterArrival[44])));
	EchoClient44.SetAttribute ("PacketSize", UintegerValue (GenerateRandText(1000)));

	UdpEchoClientHelper EchoClient45 (pod3_Iface28.GetAddress (0), 9);
	EchoClient45.SetAttribute ("MaxPackets", UintegerValue (200000));
	EchoClient45.SetAttribute ("Interval", TimeValue (Seconds (InterArrival[45])));
	EchoClient45.SetAttribute ("PacketSize", UintegerValue (GenerateRandText(1000)));

	UdpEchoClientHelper EchoClient46 (pod3_Iface29.GetAddress (0), 9);
	EchoClient46.SetAttribute ("MaxPackets", UintegerValue (200000));
	EchoClient46.SetAttribute ("Interval", TimeValue (Seconds (InterArrival[46])));
	EchoClient46.SetAttribute ("PacketSize", UintegerValue (GenerateRandText(1000)));
		
	UdpEchoClientHelper EchoClient47 (pod3_Iface30.GetAddress (0), 9);
	EchoClient47.SetAttribute ("MaxPackets", UintegerValue (200000));
	EchoClient47.SetAttribute ("Interval", TimeValue (Seconds (InterArrival[47])));
	EchoClient47.SetAttribute ("PacketSize", UintegerValue (GenerateRandText(1000)));

	UdpEchoClientHelper EchoClient48 (pod3_Iface31.GetAddress (0), 9);
	EchoClient48.SetAttribute ("MaxPackets", UintegerValue (200000));
	EchoClient48.SetAttribute ("Interval", TimeValue (Seconds (InterArrival[48])));
	EchoClient48.SetAttribute ("PacketSize", UintegerValue (GenerateRandText(1000)));

	UdpEchoClientHelper EchoClient49 (pod0_Iface.GetAddress (0), 9);
	EchoClient49.SetAttribute ("MaxPackets", UintegerValue (200000));
	EchoClient49.SetAttribute ("Interval", TimeValue (Seconds (InterArrival[49])));
	EchoClient49.SetAttribute ("PacketSize", UintegerValue (GenerateRandText(1000)));
	
	UdpEchoClientHelper EchoClient50 (pod0_Iface2.GetAddress (0), 9);
	EchoClient50.SetAttribute ("MaxPackets", UintegerValue (200000));
	EchoClient50.SetAttribute ("Interval", TimeValue (Seconds (InterArrival[50])));
	EchoClient50.SetAttribute ("PacketSize", UintegerValue (GenerateRandText(1000)));
	
	UdpEchoClientHelper EchoClient51 (pod0_Iface3.GetAddress (0), 9);
	EchoClient51.SetAttribute ("MaxPackets", UintegerValue (200000));
	EchoClient51.SetAttribute ("Interval", TimeValue (Seconds (InterArrival[51])));
	EchoClient51.SetAttribute ("PacketSize", UintegerValue (GenerateRandText(1000)));
	
	UdpEchoClientHelper EchoClient52 (pod0_Iface4.GetAddress (0), 9);
	EchoClient52.SetAttribute ("MaxPackets", UintegerValue (200000));
	EchoClient52.SetAttribute ("Interval", TimeValue (Seconds (InterArrival[52])));
	EchoClient52.SetAttribute ("PacketSize", UintegerValue (GenerateRandText(1000)));
	
	UdpEchoClientHelper EchoClient53 (pod0_Iface5.GetAddress (0), 9);
	EchoClient53.SetAttribute ("MaxPackets", UintegerValue (200000));
	EchoClient53.SetAttribute ("Interval", TimeValue (Seconds (InterArrival[53])));
	EchoClient53.SetAttribute ("PacketSize", UintegerValue (GenerateRandText(1000)));
	
	UdpEchoClientHelper EchoClient54 (pod0_Iface6.GetAddress (0), 9);
	EchoClient54.SetAttribute ("MaxPackets", UintegerValue (200000));
	EchoClient54.SetAttribute ("Interval", TimeValue (Seconds (InterArrival[54])));
	EchoClient54.SetAttribute ("PacketSize", UintegerValue (GenerateRandText(1000)));
	
	UdpEchoClientHelper EchoClient55 (pod0_Iface7.GetAddress (0), 9);
	EchoClient55.SetAttribute ("MaxPackets", UintegerValue (200000));
	EchoClient55.SetAttribute ("Interval", TimeValue (Seconds (InterArrival[55])));
	EchoClient55.SetAttribute ("PacketSize", UintegerValue (GenerateRandText(1000)));
	
	UdpEchoClientHelper EchoClient56 (pod0_Iface8.GetAddress (0), 9);
	EchoClient56.SetAttribute ("MaxPackets", UintegerValue (200000));
	EchoClient56.SetAttribute ("Interval", TimeValue (Seconds (InterArrival[56])));
	EchoClient56.SetAttribute ("PacketSize", UintegerValue (GenerateRandText(1000)));
	
	UdpEchoClientHelper EchoClient57 (pod0_Iface9.GetAddress (0), 9);
	EchoClient57.SetAttribute ("MaxPackets", UintegerValue (200000));
	EchoClient57.SetAttribute ("Interval", TimeValue (Seconds (InterArrival[57])));
	EchoClient57.SetAttribute ("PacketSize", UintegerValue (GenerateRandText(1000)));
	
	UdpEchoClientHelper EchoClient58 (pod0_Iface10.GetAddress (0), 9);
	EchoClient58.SetAttribute ("MaxPackets", UintegerValue (200000));
	EchoClient58.SetAttribute ("Interval", TimeValue (Seconds (InterArrival[58])));
	EchoClient58.SetAttribute ("PacketSize", UintegerValue (GenerateRandText(1000)));
	
	UdpEchoClientHelper EchoClient59 (pod0_Iface11.GetAddress (0), 9);
	EchoClient59.SetAttribute ("MaxPackets", UintegerValue (200000));
	EchoClient59.SetAttribute ("Interval", TimeValue (Seconds (InterArrival[59])));
	EchoClient59.SetAttribute ("PacketSize", UintegerValue (GenerateRandText(1000)));
	
	UdpEchoClientHelper EchoClient60 (pod0_Iface12.GetAddress (0), 9);
	EchoClient60.SetAttribute ("MaxPackets", UintegerValue (200000));
	EchoClient60.SetAttribute ("Interval", TimeValue (Seconds (InterArrival[60])));
	EchoClient60.SetAttribute ("PacketSize", UintegerValue (GenerateRandText(1000)));
	
	UdpEchoClientHelper EchoClient61 (pod1_Iface.GetAddress (0), 9);
	EchoClient61.SetAttribute ("MaxPackets", UintegerValue (200000));
	EchoClient61.SetAttribute ("Interval", TimeValue (Seconds (InterArrival[61])));
	EchoClient61.SetAttribute ("PacketSize", UintegerValue (GenerateRandText(1000)));
	
	UdpEchoClientHelper EchoClient62 (pod1_Iface2.GetAddress (0), 9);
	EchoClient62.SetAttribute ("MaxPackets", UintegerValue (200000));
	EchoClient62.SetAttribute ("Interval", TimeValue (Seconds (InterArrival[62])));
	EchoClient62.SetAttribute ("PacketSize", UintegerValue (GenerateRandText(1000)));
	
	UdpEchoClientHelper EchoClient63 (pod1_Iface3.GetAddress (0), 9);
	EchoClient63.SetAttribute ("MaxPackets", UintegerValue (200000));
	EchoClient63.SetAttribute ("Interval", TimeValue (Seconds (InterArrival[63])));
	EchoClient63.SetAttribute ("PacketSize", UintegerValue (GenerateRandText(1000)));
	
	UdpEchoClientHelper EchoClient64 (pod1_Iface4.GetAddress (0), 9);
	EchoClient64.SetAttribute ("MaxPackets", UintegerValue (200000));
	EchoClient64.SetAttribute ("Interval", TimeValue (Seconds (InterArrival[64])));
	EchoClient64.SetAttribute ("PacketSize", UintegerValue (GenerateRandText(1000)));
	
	UdpEchoClientHelper EchoClient65 (pod1_Iface5.GetAddress (0), 9);
	EchoClient65.SetAttribute ("MaxPackets", UintegerValue (200000));
	EchoClient65.SetAttribute ("Interval", TimeValue (Seconds (InterArrival[65])));
	EchoClient65.SetAttribute ("PacketSize", UintegerValue (GenerateRandText(1000)));

	UdpEchoClientHelper EchoClient66 (pod1_Iface6.GetAddress (0), 9);
	EchoClient66.SetAttribute ("MaxPackets", UintegerValue (200000));
	EchoClient66.SetAttribute ("Interval", TimeValue (Seconds (InterArrival[66])));
	EchoClient66.SetAttribute ("PacketSize", UintegerValue (GenerateRandText(1000)));
	
	UdpEchoClientHelper EchoClient67 (pod1_Iface7.GetAddress (0), 9);
	EchoClient67.SetAttribute ("MaxPackets", UintegerValue (200000));
	EchoClient67.SetAttribute ("Interval", TimeValue (Seconds (InterArrival[67])));
	EchoClient67.SetAttribute ("PacketSize", UintegerValue (GenerateRandText(1000)));
	
	UdpEchoClientHelper EchoClient68 (pod1_Iface8.GetAddress (0), 9);
	EchoClient68.SetAttribute ("MaxPackets", UintegerValue (200000));
	EchoClient68.SetAttribute ("Interval", TimeValue (Seconds (InterArrival[68])));
	EchoClient68.SetAttribute ("PacketSize", UintegerValue (GenerateRandText(1000)));
	
	UdpEchoClientHelper EchoClient69 (pod1_Iface9.GetAddress (0), 9);
	EchoClient69.SetAttribute ("MaxPackets", UintegerValue (200000));
	EchoClient69.SetAttribute ("Interval", TimeValue (Seconds (InterArrival[69])));
	EchoClient69.SetAttribute ("PacketSize", UintegerValue (GenerateRandText(1000)));

	UdpEchoClientHelper EchoClient70 (pod1_Iface10.GetAddress (0), 9);
	EchoClient70.SetAttribute ("MaxPackets", UintegerValue (200000));
	EchoClient70.SetAttribute ("Interval", TimeValue (Seconds (InterArrival[70])));
	EchoClient70.SetAttribute ("PacketSize", UintegerValue (GenerateRandText(1000)));

	UdpEchoClientHelper EchoClient71 (pod1_Iface11.GetAddress (0), 9);
	EchoClient71.SetAttribute ("MaxPackets", UintegerValue (200000));
	EchoClient71.SetAttribute ("Interval", TimeValue (Seconds (InterArrival[71])));
	EchoClient71.SetAttribute ("PacketSize", UintegerValue (GenerateRandText(1000)));

	UdpEchoClientHelper EchoClient72 (pod1_Iface12.GetAddress (0), 9);
	EchoClient72.SetAttribute ("MaxPackets", UintegerValue (200000));
	EchoClient72.SetAttribute ("Interval", TimeValue (Seconds (InterArrival[72])));
	EchoClient72.SetAttribute ("PacketSize", UintegerValue (GenerateRandText(1000)));
	
	UdpEchoClientHelper EchoClient73 (pod2_Iface.GetAddress (0), 9);
	EchoClient73.SetAttribute ("MaxPackets", UintegerValue (200000));
	EchoClient73.SetAttribute ("Interval", TimeValue (Seconds (InterArrival[73])));
	EchoClient73.SetAttribute ("PacketSize", UintegerValue (GenerateRandText(1000)));
	
	UdpEchoClientHelper EchoClient74 (pod2_Iface2.GetAddress (0), 9);
	EchoClient74.SetAttribute ("MaxPackets", UintegerValue (200000));
	EchoClient74.SetAttribute ("Interval", TimeValue (Seconds (InterArrival[74])));
	EchoClient74.SetAttribute ("PacketSize", UintegerValue (GenerateRandText(1000)));
	
	UdpEchoClientHelper EchoClient75 (pod2_Iface3.GetAddress (0), 9);
	EchoClient75.SetAttribute ("MaxPackets", UintegerValue (200000));
	EchoClient75.SetAttribute ("Interval", TimeValue (Seconds (InterArrival[75])));
	EchoClient75.SetAttribute ("PacketSize", UintegerValue (GenerateRandText(1000)));
	
	UdpEchoClientHelper EchoClient76 (pod2_Iface4.GetAddress (0), 9);
	EchoClient76.SetAttribute ("MaxPackets", UintegerValue (200000));
	EchoClient76.SetAttribute ("Interval", TimeValue (Seconds (InterArrival[76])));
	EchoClient76.SetAttribute ("PacketSize", UintegerValue (GenerateRandText(1000)));
	
	UdpEchoClientHelper EchoClient77 (pod2_Iface5.GetAddress (0), 9);
	EchoClient77.SetAttribute ("MaxPackets", UintegerValue (200000));
	EchoClient77.SetAttribute ("Interval", TimeValue (Seconds (InterArrival[77])));
	EchoClient77.SetAttribute ("PacketSize", UintegerValue (GenerateRandText(1000)));
	
	UdpEchoClientHelper EchoClient78 (pod2_Iface6.GetAddress (0), 9);
	EchoClient78.SetAttribute ("MaxPackets", UintegerValue (200000));
	EchoClient78.SetAttribute ("Interval", TimeValue (Seconds (InterArrival[78])));
	EchoClient78.SetAttribute ("PacketSize", UintegerValue (GenerateRandText(1000)));
	
	UdpEchoClientHelper EchoClient79 (pod2_Iface7.GetAddress (0), 9);
	EchoClient79.SetAttribute ("MaxPackets", UintegerValue (200000));
	EchoClient79.SetAttribute ("Interval", TimeValue (Seconds (InterArrival[79])));
	EchoClient79.SetAttribute ("PacketSize", UintegerValue (GenerateRandText(1000)));
	
	UdpEchoClientHelper EchoClient80 (pod2_Iface8.GetAddress (0), 9);
	EchoClient80.SetAttribute ("MaxPackets", UintegerValue (200000));
	EchoClient80.SetAttribute ("Interval", TimeValue (Seconds (InterArrival[80])));
	EchoClient80.SetAttribute ("PacketSize", UintegerValue (GenerateRandText(1000)));
	
	UdpEchoClientHelper EchoClient81 (pod2_Iface9.GetAddress (0), 9);
	EchoClient81.SetAttribute ("MaxPackets", UintegerValue (200000));
	EchoClient81.SetAttribute ("Interval", TimeValue (Seconds (InterArrival[81])));
	EchoClient81.SetAttribute ("PacketSize", UintegerValue (GenerateRandText(1000)));
	
	UdpEchoClientHelper EchoClient82 (pod2_Iface10.GetAddress (0), 9);
	EchoClient82.SetAttribute ("MaxPackets", UintegerValue (200000));
	EchoClient82.SetAttribute ("Interval", TimeValue (Seconds (InterArrival[82])));
	EchoClient82.SetAttribute ("PacketSize", UintegerValue (GenerateRandText(1000)));
	
	UdpEchoClientHelper EchoClient83 (pod2_Iface11.GetAddress (0), 9);
	EchoClient83.SetAttribute ("MaxPackets", UintegerValue (200000));
	EchoClient83.SetAttribute ("Interval", TimeValue (Seconds (InterArrival[83])));
	EchoClient83.SetAttribute ("PacketSize", UintegerValue (GenerateRandText(1000)));
	
	UdpEchoClientHelper EchoClient84 (pod2_Iface12.GetAddress (0), 9);
	EchoClient84.SetAttribute ("MaxPackets", UintegerValue (200000));
	EchoClient84.SetAttribute ("Interval", TimeValue (Seconds (InterArrival[84])));
	EchoClient84.SetAttribute ("PacketSize", UintegerValue (GenerateRandText(1000)));
	
	UdpEchoClientHelper EchoClient85 (pod3_Iface.GetAddress (0), 9);
	EchoClient85.SetAttribute ("MaxPackets", UintegerValue (200000));
	EchoClient85.SetAttribute ("Interval", TimeValue (Seconds (InterArrival[85])));
	EchoClient85.SetAttribute ("PacketSize", UintegerValue (GenerateRandText(1000)));
	
	UdpEchoClientHelper EchoClient86 (pod3_Iface2.GetAddress (0), 9);
	EchoClient86.SetAttribute ("MaxPackets", UintegerValue (200000));
	EchoClient86.SetAttribute ("Interval", TimeValue (Seconds (InterArrival[86])));
	EchoClient86.SetAttribute ("PacketSize", UintegerValue (GenerateRandText(1000)));
	
	UdpEchoClientHelper EchoClient87 (pod3_Iface3.GetAddress (0), 9);
	EchoClient87.SetAttribute ("MaxPackets", UintegerValue (200000));
	EchoClient87.SetAttribute ("Interval", TimeValue (Seconds (InterArrival[87])));
	EchoClient87.SetAttribute ("PacketSize", UintegerValue (GenerateRandText(1000)));
	
	UdpEchoClientHelper EchoClient88 (pod3_Iface4.GetAddress (0), 9);
	EchoClient88.SetAttribute ("MaxPackets", UintegerValue (200000));
	EchoClient88.SetAttribute ("Interval", TimeValue (Seconds (InterArrival[88])));
	EchoClient88.SetAttribute ("PacketSize", UintegerValue (GenerateRandText(1000)));

	UdpEchoClientHelper EchoClient89 (pod3_Iface5.GetAddress (0), 9);
	EchoClient89.SetAttribute ("MaxPackets", UintegerValue (200000));
	EchoClient89.SetAttribute ("Interval", TimeValue (Seconds (InterArrival[89])));
	EchoClient89.SetAttribute ("PacketSize", UintegerValue (GenerateRandText(1000)));
			
	UdpEchoClientHelper EchoClient90 (pod3_Iface6.GetAddress (0), 9);
	EchoClient90.SetAttribute ("MaxPackets", UintegerValue (200000));
	EchoClient90.SetAttribute ("Interval", TimeValue (Seconds (InterArrival[90])));
	EchoClient90.SetAttribute ("PacketSize", UintegerValue (GenerateRandText(1000)));

	UdpEchoClientHelper EchoClient91 (pod3_Iface7.GetAddress (0), 9);
	EchoClient91.SetAttribute ("MaxPackets", UintegerValue (200000));
	EchoClient91.SetAttribute ("Interval", TimeValue (Seconds (InterArrival[91])));
	EchoClient91.SetAttribute ("PacketSize", UintegerValue (GenerateRandText(1000)));

	UdpEchoClientHelper EchoClient92 (pod3_Iface8.GetAddress (0), 9);
	EchoClient92.SetAttribute ("MaxPackets", UintegerValue (200000));
	EchoClient92.SetAttribute ("Interval", TimeValue (Seconds (InterArrival[92])));
	EchoClient92.SetAttribute ("PacketSize", UintegerValue (GenerateRandText(1000)));

	UdpEchoClientHelper EchoClient93 (pod3_Iface9.GetAddress (0), 9);
	EchoClient93.SetAttribute ("MaxPackets", UintegerValue (200000));
	EchoClient93.SetAttribute ("Interval", TimeValue (Seconds (InterArrival[93])));
	EchoClient93.SetAttribute ("PacketSize", UintegerValue (GenerateRandText(1000)));
		
	UdpEchoClientHelper EchoClient94 (pod3_Iface10.GetAddress (0), 9);
	EchoClient94.SetAttribute ("MaxPackets", UintegerValue (200000));
	EchoClient94.SetAttribute ("Interval", TimeValue (Seconds (InterArrival[94])));
	EchoClient94.SetAttribute ("PacketSize", UintegerValue (GenerateRandText(1000)));

	UdpEchoClientHelper EchoClient95 (pod3_Iface11.GetAddress (0), 9);
	EchoClient95.SetAttribute ("MaxPackets", UintegerValue (200000));
	EchoClient95.SetAttribute ("Interval", TimeValue (Seconds (InterArrival[95])));
	EchoClient95.SetAttribute ("PacketSize", UintegerValue (GenerateRandText(1000)));
	
	UdpEchoClientHelper EchoClient96 (pod3_Iface12.GetAddress (0), 9);
	EchoClient96.SetAttribute ("MaxPackets", UintegerValue (200000));
	EchoClient96.SetAttribute ("Interval", TimeValue (Seconds (InterArrival[96])));
	EchoClient96.SetAttribute ("PacketSize", UintegerValue (GenerateRandText(1000)));
	
	

	
	

	ApplicationContainer clientApps,clientApps2,clientApps3,clientApps4,clientApps5,clientApps6,clientApps7,clientApps8,clientApps9,clientApps10,clientApps11,clientApps12,clientApps13,
	clientApps14,clientApps15,clientApps16,clientApps17,clientApps18,clientApps19,clientApps20,clientApps21,clientApps22,clientApps23,clientApps24,clientApps25,clientApps26,clientApps27
	,clientApps28,clientApps29,clientApps30,clientApps31,clientApps32,clientApps33,clientApps34,clientApps35,clientApps36,clientApps37,clientApps38,clientApps40,clientApps41
	,clientApps42,clientApps43,clientApps44,clientApps45,clientApps46,clientApps47,clientApps48,clientApps49,clientApps50,clientApps51,clientApps52,clientApps53,clientApps54,clientApps55,clientApps56
	,clientApps57,clientApps58,clientApps59,clientApps60,clientApps61,clientApps62,clientApps63,clientApps64,clientApps65,clientApps66,clientApps67,clientApps68
	,clientApps69,clientApps70,clientApps71,clientApps72,clientApps73,clientApps74,clientApps75,clientApps76,clientApps77,clientApps78,clientApps79,clientApps80
	,clientApps81,clientApps82,clientApps83,clientApps84,clientApps85,clientApps86,clientApps87,clientApps88,clientApps89,clientApps90,clientApps91,clientApps92,clientApps93,clientApps94,
	clientApps95,clientApps96;

	clientApps = EchoClient.Install (NodeContainer(A));
	clientApps2 = EchoClient2.Install (NodeContainer(A));
	clientApps3 = EchoClient3.Install (NodeContainer(A));
	clientApps4 = EchoClient4.Install (NodeContainer(A));
	clientApps5 = EchoClient5.Install (NodeContainer(A));
	clientApps6 = EchoClient6.Install (NodeContainer(A));
	clientApps7 = EchoClient7.Install (NodeContainer(A));
	clientApps8 = EchoClient8.Install (NodeContainer(A));
	clientApps9 = EchoClient9.Install (NodeContainer(A));
	clientApps10 = EchoClient10.Install (NodeContainer(A));
	clientApps11 = EchoClient11.Install (NodeContainer(A));
	clientApps12 = EchoClient12.Install (NodeContainer(A));
	clientApps13 = EchoClient13.Install (NodeContainer(A));
	clientApps14 = EchoClient14.Install (NodeContainer(A));
	clientApps15 = EchoClient15.Install (NodeContainer(A));
	clientApps16 = EchoClient16.Install (NodeContainer(A));
	clientApps17 = EchoClient17.Install (NodeContainer(A));
	clientApps18 = EchoClient18.Install (NodeContainer(A));
	clientApps19 = EchoClient19.Install (NodeContainer(A));
	clientApps20 = EchoClient20.Install (NodeContainer(A));
	clientApps21 = EchoClient21.Install (NodeContainer(A));
	clientApps22 = EchoClient22.Install (NodeContainer(A));
	clientApps23 = EchoClient23.Install (NodeContainer(A));
	clientApps24 = EchoClient24.Install (NodeContainer(A));
	clientApps25 = EchoClient25.Install (NodeContainer(A));
	clientApps26 = EchoClient26.Install (NodeContainer(A));
	clientApps27 = EchoClient27.Install (NodeContainer(A));
	clientApps28 = EchoClient28.Install (NodeContainer(A));
	clientApps29 = EchoClient29.Install (NodeContainer(A));
	clientApps30 = EchoClient30.Install (NodeContainer(A));
	clientApps31 = EchoClient31.Install (NodeContainer(A));
	clientApps32 = EchoClient32.Install (NodeContainer(A));
	clientApps33 = EchoClient33.Install (NodeContainer(A));
	clientApps34 = EchoClient34.Install (NodeContainer(A));
	clientApps35 = EchoClient35.Install (NodeContainer(A));
	clientApps36 = EchoClient36.Install (NodeContainer(A));
	clientApps37 = EchoClient37.Install (NodeContainer(A));
	clientApps38 = EchoClient38.Install (NodeContainer(A));
	clientApps40 = EchoClient40.Install (NodeContainer(A));
	clientApps41 = EchoClient41.Install (NodeContainer(A));
	clientApps42 = EchoClient42.Install (NodeContainer(A));
	clientApps43 = EchoClient43.Install (NodeContainer(A));
	clientApps44 = EchoClient44.Install (NodeContainer(A));
	clientApps45 = EchoClient45.Install (NodeContainer(A));
	clientApps46 = EchoClient46.Install (NodeContainer(A));
	clientApps47 = EchoClient47.Install (NodeContainer(A));
	clientApps48 = EchoClient48.Install (NodeContainer(A));
	clientApps49 = EchoClient49.Install (NodeContainer(A));
	clientApps50 = EchoClient50.Install (NodeContainer(A));
	clientApps51 = EchoClient51.Install (NodeContainer(A));
	clientApps52 = EchoClient52.Install (NodeContainer(A));
	clientApps53 = EchoClient53.Install (NodeContainer(A));
	clientApps54 = EchoClient54.Install (NodeContainer(A));
	clientApps55 = EchoClient55.Install (NodeContainer(A));
	clientApps56 = EchoClient56.Install (NodeContainer(A));
	clientApps57 = EchoClient57.Install (NodeContainer(A));
	clientApps58 = EchoClient58.Install (NodeContainer(A));
	clientApps59 = EchoClient59.Install (NodeContainer(A));
	clientApps60 = EchoClient60.Install (NodeContainer(A));
	clientApps61 = EchoClient61.Install (NodeContainer(A));
	clientApps62 = EchoClient62.Install (NodeContainer(A));
	clientApps63 = EchoClient63.Install (NodeContainer(A));
	clientApps64 = EchoClient64.Install (NodeContainer(A));
	clientApps65 = EchoClient65.Install (NodeContainer(A));
	clientApps66 = EchoClient66.Install (NodeContainer(A));
	clientApps67 = EchoClient67.Install (NodeContainer(A));
	clientApps68 = EchoClient68.Install (NodeContainer(A));
	clientApps69 = EchoClient69.Install (NodeContainer(A));
	clientApps70 = EchoClient70.Install (NodeContainer(A));
	clientApps71 = EchoClient71.Install (NodeContainer(A));
	clientApps72 = EchoClient72.Install (NodeContainer(A));
	clientApps73 = EchoClient73.Install (NodeContainer(A));
	clientApps74 = EchoClient74.Install (NodeContainer(A));
	clientApps75 = EchoClient75.Install (NodeContainer(A));
	clientApps76 = EchoClient76.Install (NodeContainer(A));
	clientApps77 = EchoClient77.Install (NodeContainer(A));
	clientApps78 = EchoClient78.Install (NodeContainer(A));
	clientApps79 = EchoClient79.Install (NodeContainer(A));
	clientApps80 = EchoClient80.Install (NodeContainer(A));
	clientApps81 = EchoClient81.Install (NodeContainer(A));
	clientApps82 = EchoClient82.Install (NodeContainer(A));
	clientApps83 = EchoClient83.Install (NodeContainer(A));
	clientApps84 = EchoClient84.Install (NodeContainer(A));
	clientApps85 = EchoClient85.Install (NodeContainer(A));
	clientApps86 = EchoClient86.Install (NodeContainer(A));
	clientApps87 = EchoClient87.Install (NodeContainer(A));
	clientApps88 = EchoClient88.Install (NodeContainer(A));
	clientApps89 = EchoClient89.Install (NodeContainer(A));
	clientApps90 = EchoClient90.Install (NodeContainer(A));
	clientApps91 = EchoClient91.Install (NodeContainer(A));
	clientApps92 = EchoClient92.Install (NodeContainer(A));
	clientApps93 = EchoClient93.Install (NodeContainer(A));
	clientApps94 = EchoClient94.Install (NodeContainer(A));
	clientApps95 = EchoClient95.Install (NodeContainer(A));
	clientApps96 = EchoClient96.Install (NodeContainer(A));
	
	

	clientApps.Start (Seconds (InterArrival[1]));
	clientApps.Stop (Seconds (10.0));
	clientApps2.Start (Seconds (InterArrival[2]));
	clientApps2.Stop (Seconds (10.0));
	clientApps3.Start (Seconds (InterArrival[3]));
	clientApps3.Stop (Seconds (10.0));
	clientApps4.Start (Seconds (InterArrival[4]));
	clientApps4.Stop (Seconds (10.0));
	clientApps5.Start (Seconds (InterArrival[5]));
	clientApps5.Stop (Seconds (10.0));
	clientApps6.Start (Seconds (InterArrival[6]));
	clientApps6.Stop (Seconds (10.0));
	clientApps7.Start (Seconds (InterArrival[7]));
	clientApps7.Stop (Seconds (10.0));
	clientApps8.Start (Seconds (InterArrival[8]));
	clientApps8.Stop (Seconds (10.0));
	clientApps9.Start (Seconds (InterArrival[9]));
	clientApps9.Stop (Seconds (10.0));
	clientApps10.Start (Seconds (InterArrival[10]));
	clientApps10.Stop (Seconds (10.0));
	clientApps11.Start (Seconds (InterArrival[11]));
	clientApps11.Stop (Seconds (10.0));
	clientApps12.Start (Seconds (InterArrival[12]));
	clientApps12.Stop (Seconds (10.0));
	clientApps13.Start (Seconds (InterArrival[13]));
	clientApps13.Stop (Seconds (10.0));
	clientApps14.Start (Seconds (InterArrival[14]));
	clientApps14.Stop (Seconds (10.0));
	clientApps15.Start (Seconds (InterArrival[15]));
	clientApps15.Stop (Seconds (10.0));
	clientApps16.Start (Seconds (InterArrival[16]));
	clientApps16.Stop (Seconds (10.0));
	clientApps17.Start (Seconds (InterArrival[17]));
	clientApps17.Stop (Seconds (10.0));
	clientApps18.Start (Seconds (InterArrival[18]));
	clientApps18.Stop (Seconds (10.0));
	clientApps19.Start (Seconds (InterArrival[19]));
	clientApps19.Stop (Seconds (10.0));
	clientApps20.Start (Seconds (InterArrival[20]));
	clientApps21.Stop (Seconds (10.0));
	clientApps22.Start (Seconds (InterArrival[21]));
	clientApps22.Stop (Seconds (10.0));
	clientApps23.Start (Seconds (InterArrival[22]));
	clientApps23.Stop (Seconds (10.0));
	clientApps24.Start (Seconds (InterArrival[23]));
	clientApps24.Stop (Seconds (10.0));
	clientApps25.Start (Seconds (InterArrival[24]));
	clientApps25.Stop (Seconds (10.0));
	clientApps26.Start (Seconds (InterArrival[25]));
	clientApps26.Stop (Seconds (10.0));
	clientApps27.Start (Seconds (InterArrival[26]));
	clientApps27.Stop (Seconds (10.0));
	clientApps28.Start (Seconds (InterArrival[27]));
	clientApps28.Stop (Seconds (10.0));
	clientApps29.Start (Seconds (InterArrival[28]));
	clientApps29.Stop (Seconds (10.0));
	clientApps30.Start (Seconds (InterArrival[29]));
	clientApps30.Stop (Seconds (10.0));
	clientApps31.Start (Seconds (InterArrival[30]));
	clientApps31.Stop (Seconds (10.0));
	clientApps32.Start (Seconds (InterArrival[31]));
	clientApps32.Stop (Seconds (10.0));
	clientApps33.Start (Seconds (InterArrival[32]));
	clientApps33.Stop (Seconds (10.0));
	clientApps34.Start (Seconds (InterArrival[33]));
	clientApps34.Stop (Seconds (10.0));
	clientApps35.Start (Seconds (InterArrival[34]));
	clientApps35.Stop (Seconds (10.0));
	clientApps36.Start (Seconds (InterArrival[35]));
	clientApps36.Stop (Seconds (10.0));
	clientApps37.Start (Seconds (InterArrival[36]));
	clientApps37.Stop (Seconds (10.0));
	clientApps38.Start (Seconds (InterArrival[37]));
	clientApps38.Stop (Seconds (10.0));
	clientApps40.Start (Seconds (InterArrival[38]));
	clientApps40.Stop (Seconds (10.0));
	clientApps41.Start (Seconds (InterArrival[39]));
	clientApps41.Stop (Seconds (10.0));
	clientApps42.Start (Seconds (InterArrival[40]));
	clientApps42.Stop (Seconds (10.0));
	clientApps43.Start (Seconds (InterArrival[41]));
	clientApps43.Stop (Seconds (10.0));
	clientApps44.Start (Seconds (InterArrival[42]));
	clientApps44.Stop (Seconds (10.0));
	clientApps45.Start (Seconds (InterArrival[43]));
	clientApps45.Stop (Seconds (10.0));
	clientApps46.Start (Seconds (InterArrival[44]));
	clientApps46.Stop (Seconds (10.0));
	clientApps47.Start (Seconds (InterArrival[45]));
	clientApps47.Stop (Seconds (10.0));
	clientApps48.Start (Seconds (InterArrival[46]));
	clientApps48.Stop (Seconds (10.0));
	clientApps49.Start (Seconds (InterArrival[47]));
	clientApps49.Stop (Seconds (10.0));
	clientApps50.Start (Seconds (InterArrival[48]));
	clientApps50.Stop (Seconds (10.0));
	clientApps51.Start (Seconds (InterArrival[49]));
	clientApps51.Stop (Seconds (10.0));
	clientApps52.Start (Seconds (InterArrival[50]));
	clientApps52.Stop (Seconds (10.0));
	clientApps53.Start (Seconds (InterArrival[51]));
	clientApps53.Stop (Seconds (10.0));
	clientApps54.Start (Seconds (InterArrival[52]));
	clientApps54.Stop (Seconds (10.0));
	clientApps55.Start (Seconds (InterArrival[53]));
	clientApps55.Stop (Seconds (10.0));
	clientApps56.Start (Seconds (InterArrival[54]));
	clientApps56.Stop (Seconds (10.0));
	clientApps57.Start (Seconds (InterArrival[55]));
	clientApps57.Stop (Seconds (10.0));
	clientApps58.Start (Seconds (InterArrival[56]));
	clientApps58.Stop (Seconds (10.0));
	clientApps59.Start (Seconds (InterArrival[57]));
	clientApps59.Stop (Seconds (10.0));
	clientApps60.Start (Seconds (InterArrival[58]));
	clientApps60.Stop (Seconds (10.0));
	clientApps61.Start (Seconds (InterArrival[59]));
	clientApps61.Stop (Seconds (10.0));
	clientApps62.Start (Seconds (InterArrival[60]));
	clientApps62.Stop (Seconds (10.0));
	clientApps63.Start (Seconds (InterArrival[61]));
	clientApps63.Stop (Seconds (10.0));
	clientApps64.Start (Seconds (InterArrival[62]));
	clientApps64.Stop (Seconds (10.0));
	clientApps65.Start (Seconds (InterArrival[63]));
	clientApps65.Stop (Seconds (10.0));
	clientApps66.Start (Seconds (InterArrival[64]));
	clientApps66.Stop (Seconds (10.0));
	clientApps67.Start (Seconds (InterArrival[65]));
	clientApps67.Stop (Seconds (10.0));
	clientApps69.Start (Seconds (InterArrival[67]));
	clientApps69.Stop (Seconds (10.0));
	clientApps70.Start (Seconds (InterArrival[68]));
	clientApps70.Stop (Seconds (10.0));
	clientApps71.Start (Seconds (InterArrival[69]));
	clientApps71.Stop (Seconds (10.0));
	clientApps72.Start (Seconds (InterArrival[70]));
	clientApps72.Stop (Seconds (10.0));
	clientApps73.Start (Seconds (InterArrival[71]));
	clientApps73.Stop (Seconds (10.0));
	clientApps74.Start (Seconds (InterArrival[72]));
	clientApps74.Stop (Seconds (10.0));
	clientApps75.Start (Seconds (InterArrival[73]));
	clientApps75.Stop (Seconds (10.0));
	clientApps76.Start (Seconds (InterArrival[74]));
	clientApps76.Stop (Seconds (10.0));
	clientApps77.Start (Seconds (InterArrival[75]));
	clientApps77.Stop (Seconds (10.0));
	clientApps78.Start (Seconds (InterArrival[76]));
	clientApps78.Stop (Seconds (10.0));
	clientApps79.Start (Seconds (InterArrival[77]));
	clientApps79.Stop (Seconds (10.0));
	clientApps80.Start (Seconds (InterArrival[78]));
	clientApps80.Stop (Seconds (10.0));
	clientApps81.Start (Seconds (InterArrival[79]));
	clientApps81.Stop (Seconds (10.0));
	clientApps82.Start (Seconds (InterArrival[80]));
	clientApps82.Stop (Seconds (10.0));
	clientApps83.Start (Seconds (InterArrival[81]));
	clientApps83.Stop (Seconds (10.0));
	clientApps84.Start (Seconds (InterArrival[82]));
	clientApps84.Stop (Seconds (10.0));
	clientApps85.Start (Seconds (InterArrival[83]));
	clientApps85.Stop (Seconds (10.0));
	clientApps86.Start (Seconds (InterArrival[84]));
	clientApps86.Stop (Seconds (10.0));
	clientApps87.Start (Seconds (InterArrival[85]));
	clientApps87.Stop (Seconds (10.0));
	clientApps88.Start (Seconds (InterArrival[86]));
	clientApps88.Stop (Seconds (10.0));
	clientApps89.Start (Seconds (InterArrival[87]));
	clientApps89.Stop (Seconds (10.0));
	clientApps90.Start (Seconds (InterArrival[88]));
	clientApps90.Stop (Seconds (10.0));
	clientApps91.Start (Seconds (InterArrival[89]));
	clientApps91.Stop (Seconds (10.0));
	clientApps92.Start (Seconds (InterArrival[90]));
	clientApps92.Stop (Seconds (10.0));
	clientApps93.Start (Seconds (InterArrival[91]));
	clientApps93.Stop (Seconds (10.0));
	clientApps94.Start (Seconds (InterArrival[92]));
	clientApps94.Stop (Seconds (10.0));
	clientApps95.Start (Seconds (InterArrival[93]));
	clientApps95.Stop (Seconds (10.0));
	clientApps96.Start (Seconds (InterArrival[94]));
	clientApps96.Stop (Seconds (10.0));


	//tcp flow
	
	cout<<"Time for Sinks"<<"\n";
	srand(time(NULL));		
	
	int tcpSegmentSize = 1024; 
	uint32_t maxBytes = 1000000; // 0 means "unlimited"
	Config::SetDefault ("ns3::TcpSocket::SegmentSize", UintegerValue (tcpSegmentSize));
	Config::SetDefault ("ns3::TcpSocket::DelAckCount", UintegerValue (0)); 
	uint16_t port = 80 , port2 = 90 ; 

	Address sinkAddr(InetSocketAddress (pod0_Iface21.GetAddress (0), port)); 
	Address sinkAddr2(InetSocketAddress (pod0_Iface22.GetAddress (0), port2)); 
	Address sinkAddr3(InetSocketAddress (pod0_Iface23.GetAddress (0), port)); 
	Address sinkAddr4(InetSocketAddress (pod0_Iface24.GetAddress (0), port2)); 
	Address sinkAddr5(InetSocketAddress (pod0_Iface25.GetAddress (0), port));
	Address sinkAddr6(InetSocketAddress (pod0_Iface26.GetAddress (0), port2));
	Address sinkAddr7(InetSocketAddress (pod0_Iface27.GetAddress (0), port));
	Address sinkAddr8(InetSocketAddress (pod0_Iface28.GetAddress (0), port2));
	Address sinkAddr9(InetSocketAddress (pod0_Iface29.GetAddress (0), port));
	Address sinkAddr10(InetSocketAddress (pod0_Iface30.GetAddress (0), port2));
	Address sinkAddr11(InetSocketAddress (pod0_Iface31.GetAddress (0), port));
	Address sinkAddr12(InetSocketAddress (pod0_Iface32.GetAddress (0), port2));
	Address sinkAddr13(InetSocketAddress (pod0_Iface.GetAddress (0), port)); 
	Address sinkAddr14(InetSocketAddress (pod0_Iface2.GetAddress (0), port2)); 
	Address sinkAddr15(InetSocketAddress (pod0_Iface3.GetAddress (0), port)); 
	Address sinkAddr16(InetSocketAddress (pod0_Iface4.GetAddress (0), port2)); 
	Address sinkAddr17(InetSocketAddress (pod0_Iface5.GetAddress (0), port));
	Address sinkAddr18(InetSocketAddress (pod0_Iface6.GetAddress (0), port2));
	Address sinkAddr19(InetSocketAddress (pod0_Iface7.GetAddress (0), port));
	Address sinkAddr20(InetSocketAddress (pod0_Iface8.GetAddress (0), port2));
	Address sinkAddr21(InetSocketAddress (pod0_Iface9.GetAddress (0), port));
	Address sinkAddr22(InetSocketAddress (pod0_Iface10.GetAddress (0), port2));
	Address sinkAddr23(InetSocketAddress (pod0_Iface11.GetAddress (0), port));
	Address sinkAddr24(InetSocketAddress (pod0_Iface12.GetAddress (0), port2));

	PacketSinkHelper sink ("ns3::TcpSocketFactory", sinkAddr); 
	PacketSinkHelper sink2 ("ns3::TcpSocketFactory", sinkAddr2); 		
	PacketSinkHelper sink3 ("ns3::TcpSocketFactory", sinkAddr3); 
	PacketSinkHelper sink4 ("ns3::TcpSocketFactory", sinkAddr4);
	PacketSinkHelper sink5 ("ns3::TcpSocketFactory", sinkAddr5); 
	PacketSinkHelper sink6 ("ns3::TcpSocketFactory", sinkAddr6); 
	PacketSinkHelper sink7 ("ns3::TcpSocketFactory", sinkAddr7); 
	PacketSinkHelper sink8 ("ns3::TcpSocketFactory", sinkAddr8); 		
	PacketSinkHelper sink9 ("ns3::TcpSocketFactory", sinkAddr9); 
	PacketSinkHelper sink10 ("ns3::TcpSocketFactory", sinkAddr10);
	PacketSinkHelper sink11 ("ns3::TcpSocketFactory", sinkAddr11); 
	PacketSinkHelper sink12 ("ns3::TcpSocketFactory", sinkAddr12); 
	PacketSinkHelper sink13 ("ns3::TcpSocketFactory", sinkAddr13); 
	PacketSinkHelper sink14 ("ns3::TcpSocketFactory", sinkAddr14); 		
	PacketSinkHelper sink15 ("ns3::TcpSocketFactory", sinkAddr15); 
	PacketSinkHelper sink16 ("ns3::TcpSocketFactory", sinkAddr16);
	PacketSinkHelper sink17 ("ns3::TcpSocketFactory", sinkAddr17); 
	PacketSinkHelper sink18 ("ns3::TcpSocketFactory", sinkAddr18); 
	PacketSinkHelper sink19 ("ns3::TcpSocketFactory", sinkAddr19); 
	PacketSinkHelper sink20 ("ns3::TcpSocketFactory", sinkAddr20); 		
	PacketSinkHelper sink21 ("ns3::TcpSocketFactory", sinkAddr21); 
	PacketSinkHelper sink22 ("ns3::TcpSocketFactory", sinkAddr22);
	PacketSinkHelper sink23 ("ns3::TcpSocketFactory", sinkAddr23); 
	PacketSinkHelper sink24 ("ns3::TcpSocketFactory", sinkAddr24); 
 		
	ApplicationContainer sinkApp = sink.Install (pod0.Get(0)); 
	ApplicationContainer sinkApp2 = sink2.Install (pod0.Get(0)); 
	ApplicationContainer sinkApp3 = sink3.Install (pod0.Get(1)); 
	ApplicationContainer sinkApp4 = sink4.Install (pod0.Get(1));
	ApplicationContainer sinkApp5 = sink5.Install (pod0.Get(2));
	ApplicationContainer sinkApp6 = sink6.Install (pod0.Get(2));
	ApplicationContainer sinkApp7 = sink7.Install (pod0.Get(3)); 
	ApplicationContainer sinkApp8 = sink8.Install (pod0.Get(3)); 
	ApplicationContainer sinkApp9 = sink9.Install (pod0.Get(4)); 
	ApplicationContainer sinkApp10 = sink10.Install (pod0.Get(4));
	ApplicationContainer sinkApp11 = sink11.Install (pod0.Get(5));
	ApplicationContainer sinkApp12 = sink12.Install (pod0.Get(5));
	ApplicationContainer sinkApp13 = sink13.Install (pod0.Get(0)); 
	ApplicationContainer sinkApp14 = sink14.Install (pod0.Get(0)); 
	ApplicationContainer sinkApp15 = sink15.Install (pod0.Get(1)); 
	ApplicationContainer sinkApp16 = sink16.Install (pod0.Get(1));
	ApplicationContainer sinkApp17 = sink17.Install (pod0.Get(2));
	ApplicationContainer sinkApp18 = sink18.Install (pod0.Get(2));
	ApplicationContainer sinkApp19 = sink19.Install (pod0.Get(3)); 
	ApplicationContainer sinkApp20 = sink20.Install (pod0.Get(3)); 
	ApplicationContainer sinkApp21 = sink21.Install (pod0.Get(4)); 
	ApplicationContainer sinkApp22 = sink22.Install (pod0.Get(4));
	ApplicationContainer sinkApp23 = sink23.Install (pod0.Get(5));
	ApplicationContainer sinkApp24 = sink24.Install (pod0.Get(5));
	
	sinkApp.Start (Seconds (GenerateRandReply(0.05))); 
	sinkApp.Stop (Seconds (10.0));
	sinkApp2.Start (Seconds (GenerateRandReply(0.05))); 
	sinkApp2.Stop (Seconds (10.0));
	sinkApp3.Start (Seconds (GenerateRandReply(0.05))); 
	sinkApp3.Stop (Seconds (10.0));
	sinkApp4.Start (Seconds (GenerateRandReply(0.05))); 
	sinkApp4.Stop (Seconds (10.0));
	sinkApp5.Start (Seconds (GenerateRandReply(0.05))); 
	sinkApp5.Stop (Seconds (10.0));
	sinkApp6.Start (Seconds (GenerateRandReply(0.05))); 
	sinkApp6.Stop (Seconds (10.0));
	sinkApp7.Start (Seconds (GenerateRandReply(0.05))); 
	sinkApp7.Stop (Seconds (10.0));
	sinkApp8.Start (Seconds (GenerateRandReply(0.05))); 
	sinkApp8.Stop (Seconds (10.0));
	sinkApp9.Start (Seconds (GenerateRandReply(0.05))); 
	sinkApp9.Stop (Seconds (10.0));
	sinkApp10.Start (Seconds (GenerateRandReply(0.05))); 
	sinkApp10.Stop (Seconds (10.0));
	sinkApp11.Start (Seconds (GenerateRandReply(0.05))); 
	sinkApp11.Stop (Seconds (10.0));
	sinkApp12.Start (Seconds (GenerateRandReply(0.05))); 
	sinkApp12.Stop (Seconds (10.0));
	sinkApp13.Start (Seconds (GenerateRandReply(0.05))); 
	sinkApp13.Stop (Seconds (10.0));
	sinkApp14.Start (Seconds (GenerateRandReply(0.05))); 
	sinkApp14.Stop (Seconds (10.0));
	sinkApp15.Start (Seconds (GenerateRandReply(0.05))); 
	sinkApp15.Stop (Seconds (10.0));
	sinkApp16.Start (Seconds (GenerateRandReply(0.05))); 
	sinkApp16.Stop (Seconds (10.0));
	sinkApp17.Start (Seconds (GenerateRandReply(0.05))); 
	sinkApp17.Stop (Seconds (10.0));
	sinkApp18.Start (Seconds (GenerateRandReply(0.05))); 
	sinkApp18.Stop (Seconds (10.0));
	sinkApp19.Start (Seconds (GenerateRandReply(0.05))); 
	sinkApp19.Stop (Seconds (10.0));
	sinkApp20.Start (Seconds (GenerateRandReply(0.05))); 
	sinkApp20.Stop (Seconds (10.0));
	sinkApp21.Start (Seconds (GenerateRandReply(0.05))); 
	sinkApp21.Stop (Seconds (10.0));
	sinkApp22.Start (Seconds (GenerateRandReply(0.05))); 
	sinkApp22.Stop (Seconds (10.0));
	sinkApp23.Start (Seconds (GenerateRandReply(0.05))); 
	sinkApp23.Stop (Seconds (10.0));
	sinkApp24.Start (Seconds (GenerateRandReply(0.05))); 
	sinkApp24.Stop (Seconds (10.0));
	
	
	BulkSendHelper sourceAhelper ("ns3::TcpSocketFactory", sinkAddr);
	BulkSendHelper sourceAhelper2 ("ns3::TcpSocketFactory", sinkAddr2); 
	BulkSendHelper sourceAhelper3 ("ns3::TcpSocketFactory", sinkAddr3);
	BulkSendHelper sourceAhelper4 ("ns3::TcpSocketFactory", sinkAddr4);
	BulkSendHelper sourceAhelper5 ("ns3::TcpSocketFactory", sinkAddr5);
	BulkSendHelper sourceAhelper6 ("ns3::TcpSocketFactory", sinkAddr6);
	BulkSendHelper sourceAhelper7 ("ns3::TcpSocketFactory", sinkAddr7);
	BulkSendHelper sourceAhelper8 ("ns3::TcpSocketFactory", sinkAddr8); 
	BulkSendHelper sourceAhelper9 ("ns3::TcpSocketFactory", sinkAddr9);
	BulkSendHelper sourceAhelper10 ("ns3::TcpSocketFactory", sinkAddr10);
	BulkSendHelper sourceAhelper11 ("ns3::TcpSocketFactory", sinkAddr11);
	BulkSendHelper sourceAhelper12 ("ns3::TcpSocketFactory", sinkAddr12);
	BulkSendHelper sourceAhelper13 ("ns3::TcpSocketFactory", sinkAddr13);
	BulkSendHelper sourceAhelper14 ("ns3::TcpSocketFactory", sinkAddr14); 
	BulkSendHelper sourceAhelper15 ("ns3::TcpSocketFactory", sinkAddr15);
	BulkSendHelper sourceAhelper16 ("ns3::TcpSocketFactory", sinkAddr16);
	BulkSendHelper sourceAhelper17 ("ns3::TcpSocketFactory", sinkAddr17);
	BulkSendHelper sourceAhelper18 ("ns3::TcpSocketFactory", sinkAddr18);
	BulkSendHelper sourceAhelper19 ("ns3::TcpSocketFactory", sinkAddr19);
	BulkSendHelper sourceAhelper20 ("ns3::TcpSocketFactory", sinkAddr20); 
	BulkSendHelper sourceAhelper21 ("ns3::TcpSocketFactory", sinkAddr21);
	BulkSendHelper sourceAhelper22 ("ns3::TcpSocketFactory", sinkAddr22);
	BulkSendHelper sourceAhelper23 ("ns3::TcpSocketFactory", sinkAddr23);
	BulkSendHelper sourceAhelper24 ("ns3::TcpSocketFactory", sinkAddr24);
	

	
	Address sinkAddr25(InetSocketAddress (pod1_Iface21.GetAddress (0), port)); 
	Address sinkAddr26(InetSocketAddress (pod1_Iface22.GetAddress (0), port2)); 
	Address sinkAddr27(InetSocketAddress (pod1_Iface23.GetAddress (0), port)); 
	Address sinkAddr28(InetSocketAddress (pod1_Iface24.GetAddress (0), port2)); 
	Address sinkAddr29(InetSocketAddress (pod1_Iface25.GetAddress (0), port));
	Address sinkAddr30(InetSocketAddress (pod1_Iface26.GetAddress (0), port2));
	Address sinkAddr31(InetSocketAddress (pod1_Iface27.GetAddress (0), port));
	Address sinkAddr32(InetSocketAddress (pod1_Iface28.GetAddress (0), port2));
	Address sinkAddr33(InetSocketAddress (pod1_Iface29.GetAddress (0), port));
	Address sinkAddr34(InetSocketAddress (pod1_Iface30.GetAddress (0), port2));
	Address sinkAddr35(InetSocketAddress (pod1_Iface31.GetAddress (0), port));
	Address sinkAddr36(InetSocketAddress (pod1_Iface32.GetAddress (0), port2));
	Address sinkAddr37(InetSocketAddress (pod1_Iface.GetAddress (0), port)); 
	Address sinkAddr38(InetSocketAddress (pod1_Iface2.GetAddress (0), port2)); 
	Address sinkAddr39(InetSocketAddress (pod1_Iface3.GetAddress (0), port)); 
	Address sinkAddr40(InetSocketAddress (pod1_Iface4.GetAddress (0), port2)); 
	Address sinkAddr41(InetSocketAddress (pod1_Iface5.GetAddress (0), port));
	Address sinkAddr42(InetSocketAddress (pod1_Iface6.GetAddress (0), port2));
	Address sinkAddr43(InetSocketAddress (pod1_Iface7.GetAddress (0), port));
	Address sinkAddr44(InetSocketAddress (pod1_Iface8.GetAddress (0), port2));
	Address sinkAddr45(InetSocketAddress (pod1_Iface9.GetAddress (0), port));
	Address sinkAddr46(InetSocketAddress (pod1_Iface10.GetAddress (0), port2));
	Address sinkAddr47(InetSocketAddress (pod1_Iface11.GetAddress (0), port));
	Address sinkAddr48(InetSocketAddress (pod1_Iface12.GetAddress (0), port2));

	PacketSinkHelper sink25 ("ns3::TcpSocketFactory", sinkAddr25); 
	PacketSinkHelper sink26 ("ns3::TcpSocketFactory", sinkAddr26); 		
	PacketSinkHelper sink27 ("ns3::TcpSocketFactory", sinkAddr27); 
	PacketSinkHelper sink28 ("ns3::TcpSocketFactory", sinkAddr28);
	PacketSinkHelper sink29 ("ns3::TcpSocketFactory", sinkAddr29); 
	PacketSinkHelper sink30 ("ns3::TcpSocketFactory", sinkAddr30); 
	PacketSinkHelper sink31 ("ns3::TcpSocketFactory", sinkAddr31); 
	PacketSinkHelper sink32 ("ns3::TcpSocketFactory", sinkAddr32); 		
	PacketSinkHelper sink33 ("ns3::TcpSocketFactory", sinkAddr33); 
	PacketSinkHelper sink34 ("ns3::TcpSocketFactory", sinkAddr34);
	PacketSinkHelper sink35 ("ns3::TcpSocketFactory", sinkAddr35); 
	PacketSinkHelper sink36 ("ns3::TcpSocketFactory", sinkAddr36); 
	PacketSinkHelper sink37 ("ns3::TcpSocketFactory", sinkAddr37); 
	PacketSinkHelper sink38 ("ns3::TcpSocketFactory", sinkAddr38); 		
	PacketSinkHelper sink39 ("ns3::TcpSocketFactory", sinkAddr39); 
	PacketSinkHelper sink40 ("ns3::TcpSocketFactory", sinkAddr40);
	PacketSinkHelper sink41 ("ns3::TcpSocketFactory", sinkAddr41); 
	PacketSinkHelper sink42 ("ns3::TcpSocketFactory", sinkAddr42); 
	PacketSinkHelper sink43 ("ns3::TcpSocketFactory", sinkAddr43); 
	PacketSinkHelper sink44 ("ns3::TcpSocketFactory", sinkAddr44); 		
	PacketSinkHelper sink45 ("ns3::TcpSocketFactory", sinkAddr45); 
	PacketSinkHelper sink46 ("ns3::TcpSocketFactory", sinkAddr46);
	PacketSinkHelper sink47 ("ns3::TcpSocketFactory", sinkAddr47); 
	PacketSinkHelper sink48 ("ns3::TcpSocketFactory", sinkAddr48); 
		
	ApplicationContainer sinkApp25 = sink25.Install (pod1.Get(0)); 
	ApplicationContainer sinkApp26 = sink26.Install (pod1.Get(0)); 
	ApplicationContainer sinkApp27 = sink27.Install (pod1.Get(1)); 
	ApplicationContainer sinkApp28 = sink28.Install (pod1.Get(1));
	ApplicationContainer sinkApp29 = sink29.Install (pod1.Get(2));
	ApplicationContainer sinkApp30 = sink30.Install (pod1.Get(2));
	ApplicationContainer sinkApp31 = sink31.Install (pod1.Get(3)); 
	ApplicationContainer sinkApp32 = sink32.Install (pod1.Get(3)); 
	ApplicationContainer sinkApp33 = sink33.Install (pod1.Get(4)); 
	ApplicationContainer sinkApp34 = sink34.Install (pod1.Get(4));
	ApplicationContainer sinkApp35 = sink35.Install (pod1.Get(5));
	ApplicationContainer sinkApp36 = sink36.Install (pod1.Get(5));
	ApplicationContainer sinkApp37 = sink37.Install (pod1.Get(0)); 
	ApplicationContainer sinkApp38 = sink38.Install (pod1.Get(0)); 
	ApplicationContainer sinkApp39 = sink39.Install (pod1.Get(1)); 
	ApplicationContainer sinkApp40 = sink40.Install (pod1.Get(1));
	ApplicationContainer sinkApp41 = sink41.Install (pod1.Get(2));
	ApplicationContainer sinkApp42 = sink42.Install (pod1.Get(2));
	ApplicationContainer sinkApp43 = sink43.Install (pod1.Get(3)); 
	ApplicationContainer sinkApp44 = sink44.Install (pod1.Get(3)); 
	ApplicationContainer sinkApp45 = sink45.Install (pod1.Get(4)); 
	ApplicationContainer sinkApp46 = sink46.Install (pod1.Get(4));
	ApplicationContainer sinkApp47 = sink47.Install (pod1.Get(5));
	ApplicationContainer sinkApp48 = sink48.Install (pod1.Get(5));
	
	sinkApp25.Start (Seconds (GenerateRandReply(0.05))); 
	sinkApp25.Stop (Seconds (10.0));
	sinkApp26.Start (Seconds (GenerateRandReply(0.05))); 
	sinkApp26.Stop (Seconds (10.0));
	sinkApp27.Start (Seconds (GenerateRandReply(0.05))); 
	sinkApp27.Stop (Seconds (10.0));
	sinkApp28.Start (Seconds (GenerateRandReply(0.05))); 
	sinkApp28.Stop (Seconds (10.0));
	sinkApp29.Start (Seconds (GenerateRandReply(0.05))); 
	sinkApp29.Stop (Seconds (10.0));
	sinkApp30.Start (Seconds (GenerateRandReply(0.05))); 
	sinkApp30.Stop (Seconds (10.0));
	sinkApp31.Start (Seconds (GenerateRandReply(0.05))); 
	sinkApp31.Stop (Seconds (10.0));
	sinkApp32.Start (Seconds (GenerateRandReply(0.05))); 
	sinkApp32.Stop (Seconds (10.0));
	sinkApp33.Start (Seconds (GenerateRandReply(0.05))); 
	sinkApp33.Stop (Seconds (10.0));
	sinkApp34.Start (Seconds (GenerateRandReply(0.05))); 
	sinkApp34.Stop (Seconds (10.0));
	sinkApp35.Start (Seconds (GenerateRandReply(0.05))); 
	sinkApp35.Stop (Seconds (10.0));
	sinkApp36.Start (Seconds (GenerateRandReply(0.05))); 
	sinkApp36.Stop (Seconds (10.0));
	sinkApp36.Start (Seconds (GenerateRandReply(0.05))); 
	sinkApp36.Stop (Seconds (10.0));
	sinkApp37.Start (Seconds (GenerateRandReply(0.05))); 
	sinkApp37.Stop (Seconds (10.0));
	sinkApp38.Start (Seconds (GenerateRandReply(0.05))); 
	sinkApp38.Stop (Seconds (10.0));
	sinkApp39.Start (Seconds (GenerateRandReply(0.05))); 
	sinkApp39.Stop (Seconds (10.0));
	sinkApp40.Start (Seconds (GenerateRandReply(0.05))); 
	sinkApp40.Stop (Seconds (10.0));
	sinkApp41.Start (Seconds (GenerateRandReply(0.05))); 
	sinkApp41.Stop (Seconds (10.0));
	sinkApp42.Start (Seconds (GenerateRandReply(0.05))); 
	sinkApp42.Stop (Seconds (10.0));
	sinkApp43.Start (Seconds (GenerateRandReply(0.05))); 
	sinkApp43.Stop (Seconds (10.0));
	sinkApp44.Start (Seconds (GenerateRandReply(0.05))); 
	sinkApp44.Stop (Seconds (10.0));
	sinkApp45.Start (Seconds (GenerateRandReply(0.05))); 
	sinkApp45.Stop (Seconds (10.0));
	sinkApp46.Start (Seconds (GenerateRandReply(0.05))); 
	sinkApp47.Stop (Seconds (10.0));
	sinkApp48.Start (Seconds (GenerateRandReply(0.05))); 
	sinkApp48.Stop (Seconds (10.0));
	
	
	
	BulkSendHelper sourceAhelper25 ("ns3::TcpSocketFactory", sinkAddr25);
	BulkSendHelper sourceAhelper26 ("ns3::TcpSocketFactory", sinkAddr26); 
	BulkSendHelper sourceAhelper27 ("ns3::TcpSocketFactory", sinkAddr27);
	BulkSendHelper sourceAhelper28 ("ns3::TcpSocketFactory", sinkAddr28);
	BulkSendHelper sourceAhelper29 ("ns3::TcpSocketFactory", sinkAddr29);
	BulkSendHelper sourceAhelper30 ("ns3::TcpSocketFactory", sinkAddr30);
	BulkSendHelper sourceAhelper31 ("ns3::TcpSocketFactory", sinkAddr31);
	BulkSendHelper sourceAhelper32 ("ns3::TcpSocketFactory", sinkAddr32); 
	BulkSendHelper sourceAhelper33 ("ns3::TcpSocketFactory", sinkAddr33);
	BulkSendHelper sourceAhelper34 ("ns3::TcpSocketFactory", sinkAddr34);
	BulkSendHelper sourceAhelper35 ("ns3::TcpSocketFactory", sinkAddr35);
	BulkSendHelper sourceAhelper36 ("ns3::TcpSocketFactory", sinkAddr36);
	BulkSendHelper sourceAhelper37 ("ns3::TcpSocketFactory", sinkAddr37);
	BulkSendHelper sourceAhelper38 ("ns3::TcpSocketFactory", sinkAddr38); 
	BulkSendHelper sourceAhelper39 ("ns3::TcpSocketFactory", sinkAddr39);
	BulkSendHelper sourceAhelper40 ("ns3::TcpSocketFactory", sinkAddr40);
	BulkSendHelper sourceAhelper41 ("ns3::TcpSocketFactory", sinkAddr41);
	BulkSendHelper sourceAhelper42 ("ns3::TcpSocketFactory", sinkAddr42);
	BulkSendHelper sourceAhelper43 ("ns3::TcpSocketFactory", sinkAddr43);
	BulkSendHelper sourceAhelper44 ("ns3::TcpSocketFactory", sinkAddr44); 
	BulkSendHelper sourceAhelper45 ("ns3::TcpSocketFactory", sinkAddr45);
	BulkSendHelper sourceAhelper46 ("ns3::TcpSocketFactory", sinkAddr46);
	BulkSendHelper sourceAhelper47 ("ns3::TcpSocketFactory", sinkAddr47);
	BulkSendHelper sourceAhelper48 ("ns3::TcpSocketFactory", sinkAddr48);
	
	
	Address sinkAddr49(InetSocketAddress (pod2_Iface21.GetAddress (0), port)); 
	Address sinkAddr50(InetSocketAddress (pod2_Iface22.GetAddress (0), port2)); 
	Address sinkAddr51(InetSocketAddress (pod2_Iface23.GetAddress (0), port)); 
	Address sinkAddr52(InetSocketAddress (pod2_Iface24.GetAddress (0), port2)); 
	Address sinkAddr53(InetSocketAddress (pod2_Iface25.GetAddress (0), port));
	Address sinkAddr54(InetSocketAddress (pod2_Iface26.GetAddress (0), port2));
	Address sinkAddr55(InetSocketAddress (pod2_Iface27.GetAddress (0), port)); 
	Address sinkAddr56(InetSocketAddress (pod2_Iface28.GetAddress (0), port2)); 
	Address sinkAddr57(InetSocketAddress (pod2_Iface29.GetAddress (0), port)); 
	Address sinkAddr58(InetSocketAddress (pod2_Iface30.GetAddress (0), port2)); 
	Address sinkAddr59(InetSocketAddress (pod2_Iface31.GetAddress (0), port));
	Address sinkAddr60(InetSocketAddress (pod2_Iface32.GetAddress (0), port2));
	Address sinkAddr61(InetSocketAddress (pod2_Iface.GetAddress (0), port)); 
	Address sinkAddr62(InetSocketAddress (pod2_Iface2.GetAddress (0), port2)); 
	Address sinkAddr63(InetSocketAddress (pod2_Iface3.GetAddress (0), port)); 
	Address sinkAddr64(InetSocketAddress (pod2_Iface4.GetAddress (0), port2)); 
	Address sinkAddr65(InetSocketAddress (pod2_Iface5.GetAddress (0), port));
	Address sinkAddr66(InetSocketAddress (pod2_Iface6.GetAddress (0), port2));
	Address sinkAddr67(InetSocketAddress (pod2_Iface7.GetAddress (0), port)); 
	Address sinkAddr68(InetSocketAddress (pod2_Iface8.GetAddress (0), port2)); 
	Address sinkAddr69(InetSocketAddress (pod2_Iface9.GetAddress (0), port)); 
	Address sinkAddr70(InetSocketAddress (pod2_Iface10.GetAddress (0), port2)); 
	Address sinkAddr71(InetSocketAddress (pod2_Iface11.GetAddress (0), port));
	Address sinkAddr72(InetSocketAddress (pod2_Iface12.GetAddress (0), port2));

	PacketSinkHelper sink49 ("ns3::TcpSocketFactory", sinkAddr49); 
	PacketSinkHelper sink50 ("ns3::TcpSocketFactory", sinkAddr50); 		
	PacketSinkHelper sink51 ("ns3::TcpSocketFactory", sinkAddr51); 
	PacketSinkHelper sink52 ("ns3::TcpSocketFactory", sinkAddr52);
	PacketSinkHelper sink53 ("ns3::TcpSocketFactory", sinkAddr53); 
	PacketSinkHelper sink54 ("ns3::TcpSocketFactory", sinkAddr54);
	PacketSinkHelper sink55 ("ns3::TcpSocketFactory", sinkAddr55); 
	PacketSinkHelper sink56 ("ns3::TcpSocketFactory", sinkAddr56); 		
	PacketSinkHelper sink57 ("ns3::TcpSocketFactory", sinkAddr57); 
	PacketSinkHelper sink58 ("ns3::TcpSocketFactory", sinkAddr58);
	PacketSinkHelper sink59 ("ns3::TcpSocketFactory", sinkAddr59); 
	PacketSinkHelper sink60 ("ns3::TcpSocketFactory", sinkAddr60); 
	PacketSinkHelper sink61 ("ns3::TcpSocketFactory", sinkAddr61); 
	PacketSinkHelper sink62 ("ns3::TcpSocketFactory", sinkAddr62); 		
	PacketSinkHelper sink63 ("ns3::TcpSocketFactory", sinkAddr63); 
	PacketSinkHelper sink64 ("ns3::TcpSocketFactory", sinkAddr64);
	PacketSinkHelper sink65 ("ns3::TcpSocketFactory", sinkAddr65); 
	PacketSinkHelper sink66 ("ns3::TcpSocketFactory", sinkAddr66);
	PacketSinkHelper sink67 ("ns3::TcpSocketFactory", sinkAddr67); 
	PacketSinkHelper sink68 ("ns3::TcpSocketFactory", sinkAddr68); 		
	PacketSinkHelper sink69 ("ns3::TcpSocketFactory", sinkAddr69); 
	PacketSinkHelper sink70 ("ns3::TcpSocketFactory", sinkAddr70);
	PacketSinkHelper sink71 ("ns3::TcpSocketFactory", sinkAddr71); 
	PacketSinkHelper sink72 ("ns3::TcpSocketFactory", sinkAddr72);  
 		
	ApplicationContainer sinkApp49 = sink49.Install (pod2.Get(0)); 
	ApplicationContainer sinkApp50 = sink50.Install (pod2.Get(0)); 
	ApplicationContainer sinkApp51 = sink51.Install (pod2.Get(1)); 
	ApplicationContainer sinkApp52 = sink52.Install (pod2.Get(1));
	ApplicationContainer sinkApp53 = sink53.Install (pod2.Get(2));
	ApplicationContainer sinkApp54 = sink54.Install (pod2.Get(2));
	ApplicationContainer sinkApp55 = sink55.Install (pod2.Get(3)); 
	ApplicationContainer sinkApp56 = sink56.Install (pod2.Get(3)); 
	ApplicationContainer sinkApp57 = sink57.Install (pod2.Get(4)); 
	ApplicationContainer sinkApp58 = sink58.Install (pod2.Get(4));
	ApplicationContainer sinkApp59 = sink59.Install (pod2.Get(5));
	ApplicationContainer sinkApp60 = sink60.Install (pod2.Get(5));
	ApplicationContainer sinkApp61 = sink61.Install (pod2.Get(0)); 
	ApplicationContainer sinkApp62 = sink62.Install (pod2.Get(0)); 
	ApplicationContainer sinkApp63 = sink63.Install (pod2.Get(1)); 
	ApplicationContainer sinkApp64 = sink64.Install (pod2.Get(1));
	ApplicationContainer sinkApp65 = sink65.Install (pod2.Get(2));
	ApplicationContainer sinkApp66 = sink66.Install (pod2.Get(2));
	ApplicationContainer sinkApp67 = sink67.Install (pod2.Get(3)); 
	ApplicationContainer sinkApp68 = sink68.Install (pod2.Get(3)); 
	ApplicationContainer sinkApp69 = sink69.Install (pod2.Get(4)); 
	ApplicationContainer sinkApp70 = sink70.Install (pod2.Get(4));
	ApplicationContainer sinkApp71 = sink71.Install (pod2.Get(5));
	ApplicationContainer sinkApp72 = sink72.Install (pod2.Get(5));
	
	sinkApp49.Start (Seconds (GenerateRandReply(0.05))); 
	sinkApp49.Stop (Seconds (10.0));
	sinkApp50.Start (Seconds (GenerateRandReply(0.05))); 
	sinkApp50.Stop (Seconds (10.0));
	sinkApp51.Start (Seconds (GenerateRandReply(0.05))); 
	sinkApp51.Stop (Seconds (10.0));
	sinkApp52.Start (Seconds (GenerateRandReply(0.05))); 
	sinkApp52.Stop (Seconds (10.0));
	sinkApp53.Start (Seconds (GenerateRandReply(0.05))); 
	sinkApp53.Stop (Seconds (10.0));
	sinkApp54.Start (Seconds (GenerateRandReply(0.05))); 
	sinkApp54.Stop (Seconds (10.0));
	sinkApp55.Start (Seconds (GenerateRandReply(0.05))); 
	sinkApp55.Stop (Seconds (10.0));
	sinkApp56.Start (Seconds (GenerateRandReply(0.05))); 
	sinkApp56.Stop (Seconds (10.0));
	sinkApp57.Start (Seconds (GenerateRandReply(0.05))); 
	sinkApp57.Stop (Seconds (10.0));
	sinkApp58.Start (Seconds (GenerateRandReply(0.05))); 
	sinkApp58.Stop (Seconds (10.0));
	sinkApp59.Start (Seconds (GenerateRandReply(0.05))); 
	sinkApp59.Stop (Seconds (10.0));
	sinkApp60.Start (Seconds (GenerateRandReply(0.05))); 
	sinkApp60.Stop (Seconds (10.0));
	sinkApp61.Start (Seconds (GenerateRandReply(0.05))); 
	sinkApp61.Stop (Seconds (10.0));
	sinkApp62.Start (Seconds (GenerateRandReply(0.05))); 
	sinkApp62.Stop (Seconds (10.0));
	sinkApp63.Start (Seconds (GenerateRandReply(0.05))); 
	sinkApp63.Stop (Seconds (10.0));
	sinkApp64.Start (Seconds (GenerateRandReply(0.05))); 
	sinkApp64.Stop (Seconds (10.0));
	sinkApp65.Start (Seconds (GenerateRandReply(0.05))); 
	sinkApp65.Stop (Seconds (10.0));
	sinkApp66.Start (Seconds (GenerateRandReply(0.05))); 
	sinkApp66.Stop (Seconds (10.0));
	sinkApp67.Start (Seconds (GenerateRandReply(0.05))); 
	sinkApp67.Stop (Seconds (10.0));
	sinkApp68.Start (Seconds (GenerateRandReply(0.05))); 
	sinkApp68.Stop (Seconds (10.0));
	sinkApp69.Start (Seconds (GenerateRandReply(0.05))); 
	sinkApp69.Stop (Seconds (10.0));
	sinkApp70.Start (Seconds (GenerateRandReply(0.05))); 
	sinkApp70.Stop (Seconds (10.0));
	sinkApp71.Start (Seconds (GenerateRandReply(0.05))); 
	sinkApp71.Stop (Seconds (10.0));
	sinkApp72.Start (Seconds (GenerateRandReply(0.05))); 
	sinkApp72.Stop (Seconds (10.0));

		
	
	BulkSendHelper sourceAhelper49 ("ns3::TcpSocketFactory", sinkAddr49);
	BulkSendHelper sourceAhelper50 ("ns3::TcpSocketFactory", sinkAddr50); 
	BulkSendHelper sourceAhelper51 ("ns3::TcpSocketFactory", sinkAddr51);
	BulkSendHelper sourceAhelper52 ("ns3::TcpSocketFactory", sinkAddr52);
	BulkSendHelper sourceAhelper53 ("ns3::TcpSocketFactory", sinkAddr53);
	BulkSendHelper sourceAhelper54 ("ns3::TcpSocketFactory", sinkAddr54);
	BulkSendHelper sourceAhelper55 ("ns3::TcpSocketFactory", sinkAddr55);
	BulkSendHelper sourceAhelper56 ("ns3::TcpSocketFactory", sinkAddr56); 
	BulkSendHelper sourceAhelper57 ("ns3::TcpSocketFactory", sinkAddr57);
	BulkSendHelper sourceAhelper58 ("ns3::TcpSocketFactory", sinkAddr58);
	BulkSendHelper sourceAhelper59 ("ns3::TcpSocketFactory", sinkAddr59);
	BulkSendHelper sourceAhelper60 ("ns3::TcpSocketFactory", sinkAddr60);
	BulkSendHelper sourceAhelper61 ("ns3::TcpSocketFactory", sinkAddr61);
	BulkSendHelper sourceAhelper62 ("ns3::TcpSocketFactory", sinkAddr62); 
	BulkSendHelper sourceAhelper63 ("ns3::TcpSocketFactory", sinkAddr63);
	BulkSendHelper sourceAhelper64 ("ns3::TcpSocketFactory", sinkAddr64);
	BulkSendHelper sourceAhelper65 ("ns3::TcpSocketFactory", sinkAddr65);
	BulkSendHelper sourceAhelper66 ("ns3::TcpSocketFactory", sinkAddr66);
	BulkSendHelper sourceAhelper67 ("ns3::TcpSocketFactory", sinkAddr67);
	BulkSendHelper sourceAhelper68 ("ns3::TcpSocketFactory", sinkAddr68); 
	BulkSendHelper sourceAhelper69 ("ns3::TcpSocketFactory", sinkAddr69);
	BulkSendHelper sourceAhelper70 ("ns3::TcpSocketFactory", sinkAddr70);
	BulkSendHelper sourceAhelper71 ("ns3::TcpSocketFactory", sinkAddr71);
	BulkSendHelper sourceAhelper72 ("ns3::TcpSocketFactory", sinkAddr72);




	Address sinkAddr73(InetSocketAddress (pod3_Iface21.GetAddress (0), port)); 
	Address sinkAddr74(InetSocketAddress (pod3_Iface22.GetAddress (0), port2)); 
	Address sinkAddr75(InetSocketAddress (pod3_Iface23.GetAddress (0), port)); 
	Address sinkAddr76(InetSocketAddress (pod3_Iface24.GetAddress (0), port2)); 
	Address sinkAddr77(InetSocketAddress (pod3_Iface25.GetAddress (0), port));
	Address sinkAddr78(InetSocketAddress (pod3_Iface26.GetAddress (0), port2));
	Address sinkAddr79(InetSocketAddress (pod3_Iface27.GetAddress (0), port)); 
	Address sinkAddr80(InetSocketAddress (pod3_Iface28.GetAddress (0), port2)); 
	Address sinkAddr81(InetSocketAddress (pod3_Iface29.GetAddress (0), port)); 
	Address sinkAddr82(InetSocketAddress (pod3_Iface30.GetAddress (0), port2)); 
	Address sinkAddr83(InetSocketAddress (pod3_Iface31.GetAddress (0), port));
	Address sinkAddr84(InetSocketAddress (pod3_Iface32.GetAddress (0), port2));
	Address sinkAddr85(InetSocketAddress (pod3_Iface.GetAddress (0), port)); 
	Address sinkAddr86(InetSocketAddress (pod3_Iface2.GetAddress (0), port2)); 
	Address sinkAddr87(InetSocketAddress (pod3_Iface3.GetAddress (0), port)); 
	Address sinkAddr88(InetSocketAddress (pod3_Iface4.GetAddress (0), port2)); 
	Address sinkAddr89(InetSocketAddress (pod3_Iface5.GetAddress (0), port));
	Address sinkAddr90(InetSocketAddress (pod3_Iface6.GetAddress (0), port2));
	Address sinkAddr91(InetSocketAddress (pod3_Iface7.GetAddress (0), port)); 
	Address sinkAddr92(InetSocketAddress (pod3_Iface8.GetAddress (0), port2)); 
	Address sinkAddr93(InetSocketAddress (pod3_Iface9.GetAddress (0), port)); 
	Address sinkAddr94(InetSocketAddress (pod3_Iface10.GetAddress (0), port2)); 
	Address sinkAddr95(InetSocketAddress (pod3_Iface11.GetAddress (0), port));
	Address sinkAddr96(InetSocketAddress (pod3_Iface12.GetAddress (0), port2));

	PacketSinkHelper sink73 ("ns3::TcpSocketFactory", sinkAddr73); 
	PacketSinkHelper sink74 ("ns3::TcpSocketFactory", sinkAddr74); 		
	PacketSinkHelper sink75 ("ns3::TcpSocketFactory", sinkAddr75); 
	PacketSinkHelper sink76 ("ns3::TcpSocketFactory", sinkAddr76);
	PacketSinkHelper sink77 ("ns3::TcpSocketFactory", sinkAddr77); 
	PacketSinkHelper sink78 ("ns3::TcpSocketFactory", sinkAddr78); 
	PacketSinkHelper sink79 ("ns3::TcpSocketFactory", sinkAddr79); 
	PacketSinkHelper sink80 ("ns3::TcpSocketFactory", sinkAddr80); 		
	PacketSinkHelper sink81 ("ns3::TcpSocketFactory", sinkAddr81); 
	PacketSinkHelper sink82 ("ns3::TcpSocketFactory", sinkAddr82);
	PacketSinkHelper sink83 ("ns3::TcpSocketFactory", sinkAddr83); 
	PacketSinkHelper sink84 ("ns3::TcpSocketFactory", sinkAddr84);
	PacketSinkHelper sink85 ("ns3::TcpSocketFactory", sinkAddr85); 
	PacketSinkHelper sink86 ("ns3::TcpSocketFactory", sinkAddr86); 		
	PacketSinkHelper sink87 ("ns3::TcpSocketFactory", sinkAddr87); 
	PacketSinkHelper sink88 ("ns3::TcpSocketFactory", sinkAddr88);
	PacketSinkHelper sink89 ("ns3::TcpSocketFactory", sinkAddr89); 
	PacketSinkHelper sink90 ("ns3::TcpSocketFactory", sinkAddr90); 
	PacketSinkHelper sink91 ("ns3::TcpSocketFactory", sinkAddr91); 
	PacketSinkHelper sink92 ("ns3::TcpSocketFactory", sinkAddr92); 		
	PacketSinkHelper sink93 ("ns3::TcpSocketFactory", sinkAddr93); 
	PacketSinkHelper sink94 ("ns3::TcpSocketFactory", sinkAddr94);
	PacketSinkHelper sink95 ("ns3::TcpSocketFactory", sinkAddr95); 
	PacketSinkHelper sink96 ("ns3::TcpSocketFactory", sinkAddr96);
 		
	ApplicationContainer sinkApp73 = sink73.Install (pod3.Get(0)); 
	ApplicationContainer sinkApp74 = sink74.Install (pod3.Get(0)); 
	ApplicationContainer sinkApp75 = sink75.Install (pod3.Get(1)); 
	ApplicationContainer sinkApp76 = sink76.Install (pod3.Get(1));
	ApplicationContainer sinkApp77 = sink77.Install (pod3.Get(2));
	ApplicationContainer sinkApp78 = sink78.Install (pod3.Get(2));
	ApplicationContainer sinkApp79 = sink79.Install (pod3.Get(3)); 
	ApplicationContainer sinkApp80 = sink80.Install (pod3.Get(3)); 
	ApplicationContainer sinkApp81 = sink81.Install (pod3.Get(4)); 
	ApplicationContainer sinkApp82 = sink82.Install (pod3.Get(4));
	ApplicationContainer sinkApp83 = sink83.Install (pod3.Get(5));
	ApplicationContainer sinkApp84 = sink84.Install (pod3.Get(5));
	ApplicationContainer sinkApp85 = sink85.Install (pod3.Get(0)); 
	ApplicationContainer sinkApp86 = sink86.Install (pod3.Get(0)); 
	ApplicationContainer sinkApp87 = sink87.Install (pod3.Get(1)); 
	ApplicationContainer sinkApp88 = sink88.Install (pod3.Get(1));
	ApplicationContainer sinkApp89 = sink89.Install (pod3.Get(2));
	ApplicationContainer sinkApp90 = sink90.Install (pod3.Get(2));
	ApplicationContainer sinkApp91 = sink91.Install (pod3.Get(3)); 
	ApplicationContainer sinkApp92 = sink92.Install (pod3.Get(3)); 
	ApplicationContainer sinkApp93 = sink93.Install (pod3.Get(4)); 
	ApplicationContainer sinkApp94 = sink94.Install (pod3.Get(4));
	ApplicationContainer sinkApp95 = sink95.Install (pod3.Get(5));
	ApplicationContainer sinkApp96 = sink96.Install (pod3.Get(5));
	
	sinkApp73.Start (Seconds (GenerateRandReply(0.05))); 
	sinkApp73.Stop (Seconds (10.0));
	sinkApp74.Start (Seconds (GenerateRandReply(0.05))); 
	sinkApp74.Stop (Seconds (10.0));
	sinkApp75.Start (Seconds (GenerateRandReply(0.05))); 
	sinkApp75.Stop (Seconds (10.0));
	sinkApp76.Start (Seconds (GenerateRandReply(0.05))); 
	sinkApp76.Stop (Seconds (10.0));
	sinkApp77.Start (Seconds (GenerateRandReply(0.05))); 
	sinkApp77.Stop (Seconds (10.0));
	sinkApp78.Start (Seconds (GenerateRandReply(0.05))); 
	sinkApp78.Stop (Seconds (10.0));
	sinkApp79.Start (Seconds (GenerateRandReply(0.05))); 
	sinkApp79.Stop (Seconds (10.0));
	sinkApp80.Start (Seconds (GenerateRandReply(0.05))); 
	sinkApp80.Stop (Seconds (10.0));
	sinkApp81.Start (Seconds (GenerateRandReply(0.05))); 
	sinkApp81.Stop (Seconds (10.0));
	sinkApp82.Start (Seconds (GenerateRandReply(0.05))); 
	sinkApp82.Stop (Seconds (10.0));
	sinkApp83.Start (Seconds (GenerateRandReply(0.05))); 
	sinkApp83.Stop (Seconds (10.0));
	sinkApp84.Start (Seconds (GenerateRandReply(0.05))); 
	sinkApp84.Stop (Seconds (10.0));
	sinkApp85.Start (Seconds (GenerateRandReply(0.05))); 
	sinkApp85.Stop (Seconds (10.0));
	sinkApp86.Start (Seconds (GenerateRandReply(0.05))); 
	sinkApp86.Stop (Seconds (10.0));
	sinkApp87.Start (Seconds (GenerateRandReply(0.05))); 
	sinkApp87.Stop (Seconds (10.0));
	sinkApp88.Start (Seconds (GenerateRandReply(0.05))); 
	sinkApp88.Stop (Seconds (10.0));
	sinkApp89.Start (Seconds (GenerateRandReply(0.05))); 
	sinkApp89.Stop (Seconds (10.0));
	sinkApp90.Start (Seconds (GenerateRandReply(0.05))); 
	sinkApp90.Stop (Seconds (10.0));
	sinkApp91.Start (Seconds (GenerateRandReply(0.05))); 
	sinkApp91.Stop (Seconds (10.0));
	sinkApp92.Start (Seconds (GenerateRandReply(0.05))); 
	sinkApp92.Stop (Seconds (10.0));
	sinkApp93.Start (Seconds (GenerateRandReply(0.05))); 
	sinkApp93.Stop (Seconds (10.0));
	sinkApp94.Start (Seconds (GenerateRandReply(0.05))); 
	sinkApp94.Stop (Seconds (10.0));
	sinkApp95.Start (Seconds (GenerateRandReply(0.05))); 
	sinkApp95.Stop (Seconds (10.0));
	sinkApp96.Start (Seconds (GenerateRandReply(0.05))); 
	sinkApp96.Stop (Seconds (10.0));
		
	
	BulkSendHelper sourceAhelper73 ("ns3::TcpSocketFactory", sinkAddr73);
	BulkSendHelper sourceAhelper74 ("ns3::TcpSocketFactory", sinkAddr74); 
	BulkSendHelper sourceAhelper75 ("ns3::TcpSocketFactory", sinkAddr75);
	BulkSendHelper sourceAhelper76 ("ns3::TcpSocketFactory", sinkAddr76);
	BulkSendHelper sourceAhelper77 ("ns3::TcpSocketFactory", sinkAddr77);
	BulkSendHelper sourceAhelper78 ("ns3::TcpSocketFactory", sinkAddr78);
	BulkSendHelper sourceAhelper79 ("ns3::TcpSocketFactory", sinkAddr79);
	BulkSendHelper sourceAhelper80 ("ns3::TcpSocketFactory", sinkAddr80); 
	BulkSendHelper sourceAhelper81 ("ns3::TcpSocketFactory", sinkAddr81);
	BulkSendHelper sourceAhelper82 ("ns3::TcpSocketFactory", sinkAddr82);
	BulkSendHelper sourceAhelper83 ("ns3::TcpSocketFactory", sinkAddr83);
	BulkSendHelper sourceAhelper84 ("ns3::TcpSocketFactory", sinkAddr84);
	BulkSendHelper sourceAhelper85 ("ns3::TcpSocketFactory", sinkAddr85);
	BulkSendHelper sourceAhelper86 ("ns3::TcpSocketFactory", sinkAddr86); 
	BulkSendHelper sourceAhelper87 ("ns3::TcpSocketFactory", sinkAddr87);
	BulkSendHelper sourceAhelper88 ("ns3::TcpSocketFactory", sinkAddr88);
	BulkSendHelper sourceAhelper89 ("ns3::TcpSocketFactory", sinkAddr89);
	BulkSendHelper sourceAhelper90 ("ns3::TcpSocketFactory", sinkAddr90);
	BulkSendHelper sourceAhelper91 ("ns3::TcpSocketFactory", sinkAddr91);
	BulkSendHelper sourceAhelper92 ("ns3::TcpSocketFactory", sinkAddr92); 
	BulkSendHelper sourceAhelper93 ("ns3::TcpSocketFactory", sinkAddr93);
	BulkSendHelper sourceAhelper94 ("ns3::TcpSocketFactory", sinkAddr94);
	BulkSendHelper sourceAhelper95 ("ns3::TcpSocketFactory", sinkAddr95);
	BulkSendHelper sourceAhelper96 ("ns3::TcpSocketFactory", sinkAddr96);

	sourceAhelper.SetAttribute ("MaxBytes", UintegerValue (maxBytes)); 
	sourceAhelper.SetAttribute ("SendSize", UintegerValue (tcpSegmentSize)); 
	sourceAhelper2.SetAttribute ("MaxBytes", UintegerValue (maxBytes)); 
	sourceAhelper2.SetAttribute ("SendSize", UintegerValue (tcpSegmentSize)); 
	sourceAhelper3.SetAttribute ("MaxBytes", UintegerValue (maxBytes)); 
	sourceAhelper3.SetAttribute ("SendSize", UintegerValue (tcpSegmentSize)); 
	sourceAhelper4.SetAttribute ("MaxBytes", UintegerValue (maxBytes)); 
	sourceAhelper4.SetAttribute ("SendSize", UintegerValue (tcpSegmentSize)); 
	sourceAhelper5.SetAttribute ("MaxBytes", UintegerValue (maxBytes)); 
	sourceAhelper5.SetAttribute ("SendSize", UintegerValue (tcpSegmentSize));
	sourceAhelper6.SetAttribute ("MaxBytes", UintegerValue (maxBytes)); 
	sourceAhelper6.SetAttribute ("SendSize", UintegerValue (tcpSegmentSize));
	sourceAhelper7.SetAttribute ("MaxBytes", UintegerValue (maxBytes)); 
	sourceAhelper7.SetAttribute ("SendSize", UintegerValue (tcpSegmentSize)); 
	sourceAhelper8.SetAttribute ("MaxBytes", UintegerValue (maxBytes)); 
	sourceAhelper8.SetAttribute ("SendSize", UintegerValue (tcpSegmentSize)); 
	sourceAhelper9.SetAttribute ("MaxBytes", UintegerValue (maxBytes)); 
	sourceAhelper9.SetAttribute ("SendSize", UintegerValue (tcpSegmentSize)); 
	sourceAhelper10.SetAttribute ("MaxBytes", UintegerValue (maxBytes)); 
	sourceAhelper10.SetAttribute ("SendSize", UintegerValue (tcpSegmentSize)); 
	sourceAhelper11.SetAttribute ("MaxBytes", UintegerValue (maxBytes)); 
	sourceAhelper11.SetAttribute ("SendSize", UintegerValue (tcpSegmentSize));
	sourceAhelper12.SetAttribute ("MaxBytes", UintegerValue (maxBytes)); 
	sourceAhelper12.SetAttribute ("SendSize", UintegerValue (tcpSegmentSize));

	sourceAhelper13.SetAttribute ("MaxBytes", UintegerValue (maxBytes)); 
	sourceAhelper13.SetAttribute ("SendSize", UintegerValue (tcpSegmentSize)); 
	sourceAhelper14.SetAttribute ("MaxBytes", UintegerValue (maxBytes)); 
	sourceAhelper14.SetAttribute ("SendSize", UintegerValue (tcpSegmentSize)); 
	sourceAhelper15.SetAttribute ("MaxBytes", UintegerValue (maxBytes)); 
	sourceAhelper15.SetAttribute ("SendSize", UintegerValue (tcpSegmentSize)); 
	sourceAhelper16.SetAttribute ("MaxBytes", UintegerValue (maxBytes)); 
	sourceAhelper16.SetAttribute ("SendSize", UintegerValue (tcpSegmentSize)); 
	sourceAhelper17.SetAttribute ("MaxBytes", UintegerValue (maxBytes)); 
	sourceAhelper17.SetAttribute ("SendSize", UintegerValue (tcpSegmentSize));
	sourceAhelper18.SetAttribute ("MaxBytes", UintegerValue (maxBytes)); 
	sourceAhelper18.SetAttribute ("SendSize", UintegerValue (tcpSegmentSize));
	sourceAhelper19.SetAttribute ("MaxBytes", UintegerValue (maxBytes)); 
	sourceAhelper19.SetAttribute ("SendSize", UintegerValue (tcpSegmentSize)); 
	sourceAhelper20.SetAttribute ("MaxBytes", UintegerValue (maxBytes)); 
	sourceAhelper20.SetAttribute ("SendSize", UintegerValue (tcpSegmentSize)); 
	sourceAhelper21.SetAttribute ("MaxBytes", UintegerValue (maxBytes)); 
	sourceAhelper21.SetAttribute ("SendSize", UintegerValue (tcpSegmentSize)); 
	sourceAhelper22.SetAttribute ("MaxBytes", UintegerValue (maxBytes)); 
	sourceAhelper22.SetAttribute ("SendSize", UintegerValue (tcpSegmentSize)); 
	sourceAhelper23.SetAttribute ("MaxBytes", UintegerValue (maxBytes)); 
	sourceAhelper23.SetAttribute ("SendSize", UintegerValue (tcpSegmentSize));
	sourceAhelper24.SetAttribute ("MaxBytes", UintegerValue (maxBytes)); 
	sourceAhelper24.SetAttribute ("SendSize", UintegerValue (tcpSegmentSize));
	
	sourceAhelper25.SetAttribute ("MaxBytes", UintegerValue (maxBytes)); 
	sourceAhelper25.SetAttribute ("SendSize", UintegerValue (tcpSegmentSize)); 
	sourceAhelper26.SetAttribute ("MaxBytes", UintegerValue (maxBytes)); 
	sourceAhelper26.SetAttribute ("SendSize", UintegerValue (tcpSegmentSize)); 
	sourceAhelper27.SetAttribute ("MaxBytes", UintegerValue (maxBytes)); 
	sourceAhelper27.SetAttribute ("SendSize", UintegerValue (tcpSegmentSize)); 
	sourceAhelper28.SetAttribute ("MaxBytes", UintegerValue (maxBytes)); 
	sourceAhelper28.SetAttribute ("SendSize", UintegerValue (tcpSegmentSize)); 
	sourceAhelper29.SetAttribute ("MaxBytes", UintegerValue (maxBytes)); 
	sourceAhelper29.SetAttribute ("SendSize", UintegerValue (tcpSegmentSize));
	sourceAhelper30.SetAttribute ("MaxBytes", UintegerValue (maxBytes)); 
	sourceAhelper30.SetAttribute ("SendSize", UintegerValue (tcpSegmentSize));
	sourceAhelper31.SetAttribute ("MaxBytes", UintegerValue (maxBytes)); 
	sourceAhelper31.SetAttribute ("SendSize", UintegerValue (tcpSegmentSize)); 
	sourceAhelper32.SetAttribute ("MaxBytes", UintegerValue (maxBytes)); 
	sourceAhelper32.SetAttribute ("SendSize", UintegerValue (tcpSegmentSize)); 
	sourceAhelper33.SetAttribute ("MaxBytes", UintegerValue (maxBytes)); 
	sourceAhelper33.SetAttribute ("SendSize", UintegerValue (tcpSegmentSize)); 
	sourceAhelper34.SetAttribute ("MaxBytes", UintegerValue (maxBytes)); 
	sourceAhelper34.SetAttribute ("SendSize", UintegerValue (tcpSegmentSize)); 
	sourceAhelper35.SetAttribute ("MaxBytes", UintegerValue (maxBytes)); 
	sourceAhelper35.SetAttribute ("SendSize", UintegerValue (tcpSegmentSize));
	sourceAhelper36.SetAttribute ("MaxBytes", UintegerValue (maxBytes)); 
	sourceAhelper36.SetAttribute ("SendSize", UintegerValue (tcpSegmentSize));
	
	sourceAhelper37.SetAttribute ("MaxBytes", UintegerValue (maxBytes)); 
	sourceAhelper37.SetAttribute ("SendSize", UintegerValue (tcpSegmentSize)); 
	sourceAhelper38.SetAttribute ("MaxBytes", UintegerValue (maxBytes)); 
	sourceAhelper38.SetAttribute ("SendSize", UintegerValue (tcpSegmentSize)); 
	sourceAhelper39.SetAttribute ("MaxBytes", UintegerValue (maxBytes)); 
	sourceAhelper39.SetAttribute ("SendSize", UintegerValue (tcpSegmentSize)); 
	sourceAhelper40.SetAttribute ("MaxBytes", UintegerValue (maxBytes)); 
	sourceAhelper40.SetAttribute ("SendSize", UintegerValue (tcpSegmentSize)); 
	sourceAhelper41.SetAttribute ("MaxBytes", UintegerValue (maxBytes)); 
	sourceAhelper41.SetAttribute ("SendSize", UintegerValue (tcpSegmentSize));
	sourceAhelper42.SetAttribute ("MaxBytes", UintegerValue (maxBytes)); 
	sourceAhelper42.SetAttribute ("SendSize", UintegerValue (tcpSegmentSize));
	sourceAhelper43.SetAttribute ("MaxBytes", UintegerValue (maxBytes)); 
	sourceAhelper43.SetAttribute ("SendSize", UintegerValue (tcpSegmentSize)); 
	sourceAhelper44.SetAttribute ("MaxBytes", UintegerValue (maxBytes)); 
	sourceAhelper44.SetAttribute ("SendSize", UintegerValue (tcpSegmentSize)); 
	sourceAhelper45.SetAttribute ("MaxBytes", UintegerValue (maxBytes)); 
	sourceAhelper45.SetAttribute ("SendSize", UintegerValue (tcpSegmentSize)); 
	sourceAhelper46.SetAttribute ("MaxBytes", UintegerValue (maxBytes)); 
	sourceAhelper46.SetAttribute ("SendSize", UintegerValue (tcpSegmentSize)); 
	sourceAhelper47.SetAttribute ("MaxBytes", UintegerValue (maxBytes)); 
	sourceAhelper47.SetAttribute ("SendSize", UintegerValue (tcpSegmentSize));
	sourceAhelper48.SetAttribute ("MaxBytes", UintegerValue (maxBytes)); 
	sourceAhelper48.SetAttribute ("SendSize", UintegerValue (tcpSegmentSize));
	sourceAhelper49.SetAttribute ("MaxBytes", UintegerValue (maxBytes)); 
	sourceAhelper49.SetAttribute ("SendSize", UintegerValue (tcpSegmentSize)); 
	sourceAhelper50.SetAttribute ("MaxBytes", UintegerValue (maxBytes)); 
	sourceAhelper50.SetAttribute ("SendSize", UintegerValue (tcpSegmentSize)); 
	sourceAhelper51.SetAttribute ("MaxBytes", UintegerValue (maxBytes)); 
	sourceAhelper51.SetAttribute ("SendSize", UintegerValue (tcpSegmentSize)); 
	sourceAhelper52.SetAttribute ("MaxBytes", UintegerValue (maxBytes)); 
	sourceAhelper52.SetAttribute ("SendSize", UintegerValue (tcpSegmentSize)); 
	sourceAhelper53.SetAttribute ("MaxBytes", UintegerValue (maxBytes)); 
	sourceAhelper53.SetAttribute ("SendSize", UintegerValue (tcpSegmentSize));
	sourceAhelper54.SetAttribute ("MaxBytes", UintegerValue (maxBytes)); 
	sourceAhelper54.SetAttribute ("SendSize", UintegerValue (tcpSegmentSize));
	sourceAhelper55.SetAttribute ("MaxBytes", UintegerValue (maxBytes)); 
	sourceAhelper55.SetAttribute ("SendSize", UintegerValue (tcpSegmentSize)); 
	sourceAhelper56.SetAttribute ("MaxBytes", UintegerValue (maxBytes)); 
	sourceAhelper56.SetAttribute ("SendSize", UintegerValue (tcpSegmentSize)); 
	sourceAhelper57.SetAttribute ("MaxBytes", UintegerValue (maxBytes)); 
	sourceAhelper57.SetAttribute ("SendSize", UintegerValue (tcpSegmentSize)); 
	sourceAhelper58.SetAttribute ("MaxBytes", UintegerValue (maxBytes)); 
	sourceAhelper58.SetAttribute ("SendSize", UintegerValue (tcpSegmentSize)); 
	sourceAhelper59.SetAttribute ("MaxBytes", UintegerValue (maxBytes)); 
	sourceAhelper59.SetAttribute ("SendSize", UintegerValue (tcpSegmentSize));
	sourceAhelper60.SetAttribute ("MaxBytes", UintegerValue (maxBytes)); 
	sourceAhelper60.SetAttribute ("SendSize", UintegerValue (tcpSegmentSize));

	sourceAhelper61.SetAttribute ("MaxBytes", UintegerValue (maxBytes)); 
	sourceAhelper61.SetAttribute ("SendSize", UintegerValue (tcpSegmentSize)); 
	sourceAhelper62.SetAttribute ("MaxBytes", UintegerValue (maxBytes)); 
	sourceAhelper62.SetAttribute ("SendSize", UintegerValue (tcpSegmentSize)); 
	sourceAhelper63.SetAttribute ("MaxBytes", UintegerValue (maxBytes)); 
	sourceAhelper63.SetAttribute ("SendSize", UintegerValue (tcpSegmentSize)); 
	sourceAhelper64.SetAttribute ("MaxBytes", UintegerValue (maxBytes)); 
	sourceAhelper64.SetAttribute ("SendSize", UintegerValue (tcpSegmentSize)); 
	sourceAhelper65.SetAttribute ("MaxBytes", UintegerValue (maxBytes)); 
	sourceAhelper65.SetAttribute ("SendSize", UintegerValue (tcpSegmentSize));
	sourceAhelper66.SetAttribute ("MaxBytes", UintegerValue (maxBytes)); 
	sourceAhelper66.SetAttribute ("SendSize", UintegerValue (tcpSegmentSize));
	sourceAhelper67.SetAttribute ("MaxBytes", UintegerValue (maxBytes)); 
	sourceAhelper67.SetAttribute ("SendSize", UintegerValue (tcpSegmentSize)); 
	sourceAhelper68.SetAttribute ("MaxBytes", UintegerValue (maxBytes)); 
	sourceAhelper68.SetAttribute ("SendSize", UintegerValue (tcpSegmentSize)); 
	sourceAhelper69.SetAttribute ("MaxBytes", UintegerValue (maxBytes)); 
	sourceAhelper69.SetAttribute ("SendSize", UintegerValue (tcpSegmentSize)); 
	sourceAhelper70.SetAttribute ("MaxBytes", UintegerValue (maxBytes)); 
	sourceAhelper70.SetAttribute ("SendSize", UintegerValue (tcpSegmentSize)); 
	sourceAhelper71.SetAttribute ("MaxBytes", UintegerValue (maxBytes)); 
	sourceAhelper71.SetAttribute ("SendSize", UintegerValue (tcpSegmentSize));
	sourceAhelper72.SetAttribute ("MaxBytes", UintegerValue (maxBytes)); 
	sourceAhelper72.SetAttribute ("SendSize", UintegerValue (tcpSegmentSize));
	
	sourceAhelper73.SetAttribute ("MaxBytes", UintegerValue (maxBytes)); 
	sourceAhelper73.SetAttribute ("SendSize", UintegerValue (tcpSegmentSize)); 
	sourceAhelper74.SetAttribute ("MaxBytes", UintegerValue (maxBytes)); 
	sourceAhelper74.SetAttribute ("SendSize", UintegerValue (tcpSegmentSize)); 
	sourceAhelper75.SetAttribute ("MaxBytes", UintegerValue (maxBytes)); 
	sourceAhelper75.SetAttribute ("SendSize", UintegerValue (tcpSegmentSize)); 
	sourceAhelper76.SetAttribute ("MaxBytes", UintegerValue (maxBytes)); 
	sourceAhelper76.SetAttribute ("SendSize", UintegerValue (tcpSegmentSize)); 
	sourceAhelper77.SetAttribute ("MaxBytes", UintegerValue (maxBytes)); 
	sourceAhelper77.SetAttribute ("SendSize", UintegerValue (tcpSegmentSize));
	sourceAhelper78.SetAttribute ("MaxBytes", UintegerValue (maxBytes)); 
	sourceAhelper78.SetAttribute ("SendSize", UintegerValue (tcpSegmentSize));
	sourceAhelper79.SetAttribute ("MaxBytes", UintegerValue (maxBytes)); 
	sourceAhelper79.SetAttribute ("SendSize", UintegerValue (tcpSegmentSize)); 
	sourceAhelper80.SetAttribute ("MaxBytes", UintegerValue (maxBytes)); 
	sourceAhelper80.SetAttribute ("SendSize", UintegerValue (tcpSegmentSize)); 
	sourceAhelper81.SetAttribute ("MaxBytes", UintegerValue (maxBytes)); 
	sourceAhelper81.SetAttribute ("SendSize", UintegerValue (tcpSegmentSize)); 
	sourceAhelper82.SetAttribute ("MaxBytes", UintegerValue (maxBytes)); 
	sourceAhelper82.SetAttribute ("SendSize", UintegerValue (tcpSegmentSize)); 
	sourceAhelper83.SetAttribute ("MaxBytes", UintegerValue (maxBytes)); 
	sourceAhelper83.SetAttribute ("SendSize", UintegerValue (tcpSegmentSize));
	sourceAhelper84.SetAttribute ("MaxBytes", UintegerValue (maxBytes)); 
	sourceAhelper84.SetAttribute ("SendSize", UintegerValue (tcpSegmentSize));
	
	sourceAhelper85.SetAttribute ("MaxBytes", UintegerValue (maxBytes)); 
	sourceAhelper85.SetAttribute ("SendSize", UintegerValue (tcpSegmentSize)); 
	sourceAhelper86.SetAttribute ("MaxBytes", UintegerValue (maxBytes)); 
	sourceAhelper86.SetAttribute ("SendSize", UintegerValue (tcpSegmentSize)); 
	sourceAhelper87.SetAttribute ("MaxBytes", UintegerValue (maxBytes)); 
	sourceAhelper87.SetAttribute ("SendSize", UintegerValue (tcpSegmentSize)); 
	sourceAhelper88.SetAttribute ("MaxBytes", UintegerValue (maxBytes)); 
	sourceAhelper88.SetAttribute ("SendSize", UintegerValue (tcpSegmentSize)); 
	sourceAhelper89.SetAttribute ("MaxBytes", UintegerValue (maxBytes)); 
	sourceAhelper89.SetAttribute ("SendSize", UintegerValue (tcpSegmentSize));
	sourceAhelper90.SetAttribute ("MaxBytes", UintegerValue (maxBytes)); 
	sourceAhelper90.SetAttribute ("SendSize", UintegerValue (tcpSegmentSize));
	sourceAhelper91.SetAttribute ("MaxBytes", UintegerValue (maxBytes)); 
	sourceAhelper91.SetAttribute ("SendSize", UintegerValue (tcpSegmentSize)); 
	sourceAhelper92.SetAttribute ("MaxBytes", UintegerValue (maxBytes)); 
	sourceAhelper92.SetAttribute ("SendSize", UintegerValue (tcpSegmentSize)); 
	sourceAhelper93.SetAttribute ("MaxBytes", UintegerValue (maxBytes)); 
	sourceAhelper93.SetAttribute ("SendSize", UintegerValue (tcpSegmentSize)); 
	sourceAhelper94.SetAttribute ("MaxBytes", UintegerValue (maxBytes)); 
	sourceAhelper94.SetAttribute ("SendSize", UintegerValue (tcpSegmentSize)); 
	sourceAhelper95.SetAttribute ("MaxBytes", UintegerValue (maxBytes)); 
	sourceAhelper95.SetAttribute ("SendSize", UintegerValue (tcpSegmentSize));
	sourceAhelper96.SetAttribute ("MaxBytes", UintegerValue (maxBytes)); 
	sourceAhelper96.SetAttribute ("SendSize", UintegerValue (tcpSegmentSize));
	
	ApplicationContainer sourceAppsA = sourceAhelper.Install (A); 
	ApplicationContainer sourceAppsA2 = sourceAhelper.Install (A); 
	ApplicationContainer sourceAppsA3 = sourceAhelper.Install (A); 
	ApplicationContainer sourceAppsA4 = sourceAhelper.Install (A); 
	ApplicationContainer sourceAppsA5 = sourceAhelper.Install (A);
	ApplicationContainer sourceAppsA6 = sourceAhelper.Install (A);
	ApplicationContainer sourceAppsA7 = sourceAhelper.Install (A); 
	ApplicationContainer sourceAppsA8 = sourceAhelper.Install (A); 
	ApplicationContainer sourceAppsA9 = sourceAhelper.Install (A); 
	ApplicationContainer sourceAppsA10 = sourceAhelper.Install (A); 
	ApplicationContainer sourceAppsA11 = sourceAhelper.Install (A);
	ApplicationContainer sourceAppsA12 = sourceAhelper.Install (A); 

	ApplicationContainer sourceAppsA13 = sourceAhelper.Install (A); 
	ApplicationContainer sourceAppsA14 = sourceAhelper.Install (A); 
	ApplicationContainer sourceAppsA15 = sourceAhelper.Install (A); 
	ApplicationContainer sourceAppsA16 = sourceAhelper.Install (A); 
	ApplicationContainer sourceAppsA17 = sourceAhelper.Install (A);
	ApplicationContainer sourceAppsA18 = sourceAhelper.Install (A); 
	ApplicationContainer sourceAppsA19 = sourceAhelper.Install (A); 
	ApplicationContainer sourceAppsA20 = sourceAhelper.Install (A); 
	ApplicationContainer sourceAppsA21 = sourceAhelper.Install (A); 
	ApplicationContainer sourceAppsA22 = sourceAhelper.Install (A); 
	ApplicationContainer sourceAppsA23 = sourceAhelper.Install (A);
	ApplicationContainer sourceAppsA24 = sourceAhelper.Install (A);

	ApplicationContainer sourceAppsA25 = sourceAhelper.Install (A); 
	ApplicationContainer sourceAppsA26 = sourceAhelper.Install (A); 
	ApplicationContainer sourceAppsA27 = sourceAhelper.Install (A); 
	ApplicationContainer sourceAppsA28 = sourceAhelper.Install (A); 
	ApplicationContainer sourceAppsA29 = sourceAhelper.Install (A);
	ApplicationContainer sourceAppsA30 = sourceAhelper.Install (A);
	ApplicationContainer sourceAppsA31 = sourceAhelper.Install (A); 
	ApplicationContainer sourceAppsA32 = sourceAhelper.Install (A); 
	ApplicationContainer sourceAppsA33 = sourceAhelper.Install (A); 
	ApplicationContainer sourceAppsA34 = sourceAhelper.Install (A); 
	ApplicationContainer sourceAppsA35 = sourceAhelper.Install (A);
	ApplicationContainer sourceAppsA36 = sourceAhelper.Install (A); 

	ApplicationContainer sourceAppsA37 = sourceAhelper.Install (A); 
	ApplicationContainer sourceAppsA38 = sourceAhelper.Install (A); 
	ApplicationContainer sourceAppsA39 = sourceAhelper.Install (A); 
	ApplicationContainer sourceAppsA40 = sourceAhelper.Install (A); 
	ApplicationContainer sourceAppsA41 = sourceAhelper.Install (A);
	ApplicationContainer sourceAppsA42 = sourceAhelper.Install (A);
	ApplicationContainer sourceAppsA43 = sourceAhelper.Install (A); 
	ApplicationContainer sourceAppsA44 = sourceAhelper.Install (A); 
	ApplicationContainer sourceAppsA45 = sourceAhelper.Install (A); 
	ApplicationContainer sourceAppsA46 = sourceAhelper.Install (A); 
	ApplicationContainer sourceAppsA47 = sourceAhelper.Install (A);
	ApplicationContainer sourceAppsA48 = sourceAhelper.Install (A);  

	ApplicationContainer sourceAppsA49 = sourceAhelper.Install (A); 
	ApplicationContainer sourceAppsA50 = sourceAhelper.Install (A); 
	ApplicationContainer sourceAppsA51 = sourceAhelper.Install (A);
	ApplicationContainer sourceAppsA52 = sourceAhelper.Install (A);
	ApplicationContainer sourceAppsA53 = sourceAhelper.Install (A); 
	ApplicationContainer sourceAppsA54 = sourceAhelper.Install (A); 
	ApplicationContainer sourceAppsA55 = sourceAhelper.Install (A); 
	ApplicationContainer sourceAppsA56 = sourceAhelper.Install (A); 


	ApplicationContainer sourceAppsA57 = sourceAhelper.Install (A); 
	ApplicationContainer sourceAppsA58 = sourceAhelper.Install (A); 
	ApplicationContainer sourceAppsA59 = sourceAhelper.Install (A);
	ApplicationContainer sourceAppsA60 = sourceAhelper.Install (A);
	ApplicationContainer sourceAppsA61 = sourceAhelper.Install (A);
	ApplicationContainer sourceAppsA62 = sourceAhelper.Install (A);
	ApplicationContainer sourceAppsA63 = sourceAhelper.Install (A); 
	ApplicationContainer sourceAppsA64 = sourceAhelper.Install (A); 
	ApplicationContainer sourceAppsA65 = sourceAhelper.Install (A); 
	ApplicationContainer sourceAppsA66 = sourceAhelper.Install (A); 

	ApplicationContainer sourceAppsA67 = sourceAhelper.Install (A); 
	ApplicationContainer sourceAppsA68 = sourceAhelper.Install (A); 
	ApplicationContainer sourceAppsA69 = sourceAhelper.Install (A); 
	ApplicationContainer sourceAppsA70 = sourceAhelper.Install (A); 
	ApplicationContainer sourceAppsA71 = sourceAhelper.Install (A);
	ApplicationContainer sourceAppsA72 = sourceAhelper.Install (A);
	ApplicationContainer sourceAppsA73 = sourceAhelper.Install (A); 
	ApplicationContainer sourceAppsA74 = sourceAhelper.Install (A); 
	ApplicationContainer sourceAppsA75 = sourceAhelper.Install (A); 
	ApplicationContainer sourceAppsA76 = sourceAhelper.Install (A); 

	ApplicationContainer sourceAppsA77 = sourceAhelper.Install (A); 
	ApplicationContainer sourceAppsA78 = sourceAhelper.Install (A); 
	ApplicationContainer sourceAppsA79 = sourceAhelper.Install (A); 
	ApplicationContainer sourceAppsA80 = sourceAhelper.Install (A); 
	ApplicationContainer sourceAppsA81 = sourceAhelper.Install (A);
	ApplicationContainer sourceAppsA82 = sourceAhelper.Install (A);
	ApplicationContainer sourceAppsA83 = sourceAhelper.Install (A); 
	ApplicationContainer sourceAppsA84 = sourceAhelper.Install (A); 
	ApplicationContainer sourceAppsA85 = sourceAhelper.Install (A); 
	ApplicationContainer sourceAppsA86 = sourceAhelper.Install (A); 
	
	ApplicationContainer sourceAppsA87 = sourceAhelper.Install (A); 
	ApplicationContainer sourceAppsA88 = sourceAhelper.Install (A); 
	ApplicationContainer sourceAppsA89 = sourceAhelper.Install (A); 
	ApplicationContainer sourceAppsA90 = sourceAhelper.Install (A); 
	ApplicationContainer sourceAppsA91 = sourceAhelper.Install (A);
	ApplicationContainer sourceAppsA92 = sourceAhelper.Install (A);
	ApplicationContainer sourceAppsA93 = sourceAhelper.Install (A); 
	ApplicationContainer sourceAppsA94 = sourceAhelper.Install (A); 
	ApplicationContainer sourceAppsA95 = sourceAhelper.Install (A);
	ApplicationContainer sourceAppsA96 = sourceAhelper.Install (A);
	
	
	sourceAppsA.Start (Seconds (InterArrival[1]));
	sourceAppsA.Stop (Seconds (10.0));
	sourceAppsA2.Start (Seconds (InterArrival[2]));
	sourceAppsA2.Stop (Seconds (10.0));
	sourceAppsA3.Start (Seconds (InterArrival[3]));
	sourceAppsA3.Stop (Seconds (10.0));
	sourceAppsA4.Start (Seconds (InterArrival[4]));
	sourceAppsA4.Stop (Seconds (10.0));
	sourceAppsA5.Start (Seconds (InterArrival[5]));
	sourceAppsA5.Stop (Seconds (10.0));
	sourceAppsA6.Start (Seconds (InterArrival[6]));
	sourceAppsA6 .Stop (Seconds (10.0));
	sourceAppsA7.Start (Seconds (InterArrival[7]));
	sourceAppsA7.Stop (Seconds (10.0));
	sourceAppsA8.Start (Seconds (InterArrival[8]));
	sourceAppsA8.Stop (Seconds (10.0));
	sourceAppsA9.Start (Seconds (InterArrival[9]));
	sourceAppsA9.Stop (Seconds (10.0));
	sourceAppsA10.Start (Seconds (InterArrival[10]));
	sourceAppsA10.Stop (Seconds (10.0));
	sourceAppsA11.Start (Seconds (InterArrival[11]));
	sourceAppsA11.Stop (Seconds (10.0));
	sourceAppsA12.Start (Seconds (InterArrival[12]));
	sourceAppsA12.Stop (Seconds (10.0));
	
	sourceAppsA13.Start (Seconds (InterArrival[13]));
	sourceAppsA13.Stop (Seconds (10.0));
	sourceAppsA14.Start (Seconds (InterArrival[14]));
	sourceAppsA14.Stop (Seconds (10.0));
	sourceAppsA15.Start (Seconds (InterArrival[15]));
	sourceAppsA15.Stop (Seconds (10.0));
	sourceAppsA16.Start (Seconds (InterArrival[16]));
	sourceAppsA16.Stop (Seconds (10.0));
	sourceAppsA17.Start (Seconds (InterArrival[17]));
	sourceAppsA17.Stop (Seconds (10.0));
	sourceAppsA18.Start (Seconds (InterArrival[18]));
	sourceAppsA18 .Stop (Seconds (10.0));
	sourceAppsA19.Start (Seconds (InterArrival[19]));
	sourceAppsA19.Stop (Seconds (10.0));
	sourceAppsA20.Start (Seconds (InterArrival[20]));
	sourceAppsA20.Stop (Seconds (10.0));
	sourceAppsA21.Start (Seconds (InterArrival[21]));
	sourceAppsA21.Stop (Seconds (10.0));
	sourceAppsA22.Start (Seconds (InterArrival[22]));
	sourceAppsA22.Stop (Seconds (10.0));
	sourceAppsA23.Start (Seconds (InterArrival[23]));
	sourceAppsA23.Stop (Seconds (10.0));
	sourceAppsA24.Start (Seconds (InterArrival[24]));
	sourceAppsA24.Stop (Seconds (10.0));
	sourceAppsA25.Start (Seconds (InterArrival[25]));
	sourceAppsA25.Stop (Seconds (10.0));
	
	sourceAppsA26.Start (Seconds (InterArrival[26]));
	sourceAppsA26.Stop (Seconds (10.0));
	sourceAppsA27.Start (Seconds (InterArrival[27]));
	sourceAppsA27.Stop (Seconds (10.0));
	sourceAppsA28.Start (Seconds (InterArrival[28]));
	sourceAppsA28.Stop (Seconds (10.0));
	sourceAppsA29.Start (Seconds (InterArrival[29]));
	sourceAppsA29.Stop (Seconds (10.0));
	sourceAppsA30.Start (Seconds (InterArrival[30]));
	sourceAppsA30.Stop (Seconds (10.0));
	sourceAppsA31.Start (Seconds (InterArrival[31]));
	sourceAppsA31.Stop (Seconds (10.0));
	sourceAppsA32.Start (Seconds (InterArrival[32]));
	sourceAppsA32.Stop (Seconds (10.0));
	sourceAppsA33.Start (Seconds (InterArrival[33]));
	sourceAppsA33.Stop (Seconds (10.0));
	sourceAppsA34.Start (Seconds (InterArrival[34]));
	sourceAppsA34.Stop (Seconds (10.0));
	sourceAppsA35.Start (Seconds (InterArrival[35]));
	sourceAppsA35.Stop (Seconds (10.0));
	sourceAppsA36.Start (Seconds (InterArrival[36]));
	sourceAppsA36.Stop (Seconds (10.0));
	sourceAppsA37.Start (Seconds (InterArrival[37]));
	sourceAppsA37.Stop (Seconds (10.0));
	
	sourceAppsA38.Start (Seconds (InterArrival[38]));
	sourceAppsA38.Stop (Seconds (10.0));
	sourceAppsA39.Start (Seconds (InterArrival[39]));
	sourceAppsA39.Stop (Seconds (10.0));
	sourceAppsA40.Start (Seconds (InterArrival[40]));
	sourceAppsA40.Stop (Seconds (10.0));
	sourceAppsA41.Start (Seconds (InterArrival[41]));
	sourceAppsA41.Stop (Seconds (10.0));
	sourceAppsA42.Start (Seconds (InterArrival[42]));
	sourceAppsA42.Stop (Seconds (10.0));
	sourceAppsA43.Start (Seconds (InterArrival[43]));
	sourceAppsA43.Stop (Seconds (10.0));
	sourceAppsA44.Start (Seconds (InterArrival[44]));
	sourceAppsA44.Stop (Seconds (10.0));
	sourceAppsA45.Start (Seconds (InterArrival[45]));
	sourceAppsA45.Stop (Seconds (10.0));
	sourceAppsA46.Start (Seconds (InterArrival[46]));
	sourceAppsA46.Stop (Seconds (10.0));
	sourceAppsA47.Start (Seconds (InterArrival[47]));
	sourceAppsA47.Stop (Seconds (10.0));
	sourceAppsA48.Start (Seconds (InterArrival[48]));
	sourceAppsA48.Stop (Seconds (10.0));
	
	sourceAppsA49.Start (Seconds (InterArrival[49]));
	sourceAppsA49.Stop (Seconds (10.0));
	sourceAppsA50.Start (Seconds (InterArrival[50]));
	sourceAppsA50.Stop (Seconds (10.0));
	sourceAppsA51.Start (Seconds (InterArrival[51]));
	sourceAppsA51.Stop (Seconds (10.0));
	sourceAppsA52.Start (Seconds (InterArrival[52]));
	sourceAppsA52.Stop (Seconds (10.0));
	sourceAppsA53.Start (Seconds (InterArrival[53]));
	sourceAppsA53.Stop (Seconds (10.0));
	sourceAppsA54.Start (Seconds (InterArrival[54]));
	sourceAppsA54.Stop (Seconds (10.0));
	sourceAppsA55.Start (Seconds (InterArrival[55]));
	sourceAppsA55.Stop (Seconds (10.0));
	sourceAppsA56.Start (Seconds (InterArrival[56]));
	sourceAppsA56.Stop (Seconds (10.0));
	sourceAppsA57.Start (Seconds (InterArrival[57]));
	sourceAppsA57.Stop (Seconds (10.0));
	sourceAppsA58.Start (Seconds (InterArrival[58]));
	sourceAppsA58.Stop (Seconds (10.0));
	sourceAppsA59.Start (Seconds (InterArrival[59]));
	sourceAppsA59.Stop (Seconds (10.0));
	sourceAppsA60.Start (Seconds (InterArrival[60]));
	sourceAppsA60.Stop (Seconds (10.0));
	
	
	sourceAppsA61.Start (Seconds (InterArrival[61]));
	sourceAppsA61.Stop (Seconds (10.0));
	sourceAppsA62.Start (Seconds (InterArrival[62]));
	sourceAppsA62.Stop (Seconds (10.0));
	sourceAppsA63.Start (Seconds (InterArrival[63]));
	sourceAppsA63.Stop (Seconds (10.0));
	sourceAppsA64.Start (Seconds (InterArrival[64]));
	sourceAppsA64.Stop (Seconds (10.0));
	sourceAppsA65.Start (Seconds (InterArrival[65]));
	sourceAppsA65.Stop (Seconds (10.0));
	sourceAppsA66.Start (Seconds (InterArrival[66]));
	sourceAppsA66.Stop (Seconds (10.0));
	sourceAppsA67.Start (Seconds (InterArrival[67]));
	sourceAppsA67.Stop (Seconds (10.0));
	sourceAppsA68.Start (Seconds (InterArrival[68]));
	sourceAppsA68.Stop (Seconds (10.0));
	sourceAppsA69.Start (Seconds (InterArrival[69]));
	sourceAppsA69.Stop (Seconds (10.0));
	sourceAppsA70.Start (Seconds (InterArrival[70]));
	sourceAppsA70.Stop (Seconds (10.0));
	
	sourceAppsA71.Start (Seconds (InterArrival[71]));
	sourceAppsA71.Stop (Seconds (10.0));
	sourceAppsA72.Start (Seconds (InterArrival[72]));
	sourceAppsA72.Stop (Seconds (10.0));
	sourceAppsA73.Start (Seconds (InterArrival[73]));
	sourceAppsA73.Stop (Seconds (10.0));
	sourceAppsA74.Start (Seconds (InterArrival[74]));
	sourceAppsA74.Stop (Seconds (10.0));
	sourceAppsA75.Start (Seconds (InterArrival[75]));
	sourceAppsA75.Stop (Seconds (10.0));
	sourceAppsA76.Start (Seconds (InterArrival[76]));
	sourceAppsA76.Stop (Seconds (10.0));
	sourceAppsA77.Start (Seconds (InterArrival[77]));
	sourceAppsA77.Stop (Seconds (10.0));
	sourceAppsA78.Start (Seconds (InterArrival[78]));
	sourceAppsA78.Stop (Seconds (10.0));
	sourceAppsA79.Start (Seconds (InterArrival[79]));
	sourceAppsA79.Stop (Seconds (10.0));
	sourceAppsA80.Start (Seconds (InterArrival[80]));
	sourceAppsA80.Stop (Seconds (10.0));
	sourceAppsA81.Start (Seconds (InterArrival[81]));
	sourceAppsA81.Stop (Seconds (10.0));
	
	sourceAppsA82.Start (Seconds (InterArrival[82]));
	sourceAppsA82.Stop (Seconds (10.0));
	sourceAppsA83.Start (Seconds (InterArrival[83]));
	sourceAppsA83.Stop (Seconds (10.0));
	sourceAppsA84.Start (Seconds (InterArrival[84]));
	sourceAppsA84.Stop (Seconds (10.0));
	sourceAppsA85.Start (Seconds (InterArrival[85]));
	sourceAppsA85.Stop (Seconds (10.0));
	sourceAppsA86.Start (Seconds (InterArrival[86]));
	sourceAppsA86.Stop (Seconds (10.0));
	sourceAppsA87.Start (Seconds (InterArrival[87]));
	sourceAppsA87.Stop (Seconds (10.0));
	sourceAppsA88.Start (Seconds (InterArrival[88]));
	sourceAppsA88.Stop (Seconds (10.0));
	sourceAppsA89.Start (Seconds (InterArrival[89]));
	sourceAppsA89.Stop (Seconds (10.0));
	sourceAppsA90.Start (Seconds (InterArrival[90]));
	sourceAppsA91.Stop (Seconds (10.0));
	sourceAppsA92.Start (Seconds (InterArrival[91]));
	sourceAppsA92.Stop (Seconds (10.0));
	sourceAppsA93.Start (Seconds (InterArrival[92]));
	sourceAppsA93.Stop (Seconds (10.0));
	sourceAppsA94.Start (Seconds (InterArrival[93]));
	sourceAppsA94.Stop (Seconds (10.0));
	sourceAppsA95.Start (Seconds (InterArrival[94]));
	sourceAppsA95.Stop (Seconds (10.0));
	sourceAppsA96.Start (Seconds (InterArrival[95]));
	sourceAppsA96.Stop (Seconds (10.0));
	
	NodeToSW.EnablePcapAll("UniRH_FatTree_Pcap");
	
	
	AnimationInterface anim ("UniRHFT.xml");
	anim.SetConstantPosition(pod0.Get(0),5.5, 20.0);
	anim.SetConstantPosition(pod0.Get(1),7.0, 20.0);
	anim.SetConstantPosition(pod0.Get(2),8.5, 20.0);
	anim.SetConstantPosition(pod0.Get(3),9.5, 20.0);
	anim.SetConstantPosition(pod0.Get(4),10.5, 20.0);
	anim.SetConstantPosition(pod0.Get(5),12.0, 20.0);
	anim.SetConstantPosition(sw0.Get(0),7.0, 12.0);
	anim.SetConstantPosition(sw0.Get(1),9.0, 12.0);
	anim.SetConstantPosition(sw4.Get(0),33.0, 7.0);
	anim.SetConstantPosition(sw4.Get(1),35.0, 7.0);
	
	anim.SetConstantPosition(pod1.Get(0),15.5, 20.0);
	anim.SetConstantPosition(pod1.Get(1),17.0, 20.0);
	anim.SetConstantPosition(pod1.Get(2),18.5, 20.0);
	anim.SetConstantPosition(pod1.Get(3),20.0, 20.0);
	anim.SetConstantPosition(pod1.Get(4),21.5, 20.0);
	anim.SetConstantPosition(pod1.Get(5),23.0, 20.0);
	anim.SetConstantPosition(sw1.Get(0),12.0, 12.0);
	anim.SetConstantPosition(sw1.Get(1),14.0, 12.0);
	anim.SetConstantPosition(sw5.Get(0),38.0, 7.0);
	anim.SetConstantPosition(sw5.Get(1),40.0, 7.0);
	
	
	//NodeTo
	anim.SetConstantPosition(pod2.Get(0),26.0, 20.0);
	anim.SetConstantPosition(pod2.Get(1),27.5, 20.0);
	anim.SetConstantPosition(pod2.Get(2),29.0, 20.0);
	anim.SetConstantPosition(pod2.Get(3),30.5, 20.0);
	anim.SetConstantPosition(pod2.Get(4),31.75, 20.0);
	anim.SetConstantPosition(pod2.Get(5),33.0, 20.0);
	anim.SetConstantPosition(sw2.Get(0),17.0, 12.0);
	anim.SetConstantPosition(sw2.Get(1),19.0, 12.0);
	anim.SetConstantPosition(sw6.Get(0),43.0, 7.0);
	anim.SetConstantPosition(sw6.Get(1),45.0, 7.0);
		

	anim.SetConstantPosition(pod3.Get(0),35.5, 20.0);
	anim.SetConstantPosition(pod3.Get(1),37.0, 20.0);
	anim.SetConstantPosition(pod3.Get(2),38.5, 20.0);
	anim.SetConstantPosition(pod3.Get(3),40.0, 20.0);
	anim.SetConstantPosition(pod3.Get(4),41.5, 20.0);
	anim.SetConstantPosition(pod3.Get(5),43.0, 20.0);
	anim.SetConstantPosition(sw3.Get(0),22.0, 12.0);
	anim.SetConstantPosition(sw3.Get(1),24.0, 12.0);
	anim.SetConstantPosition(sw7.Get(0),48.0, 7.0);
	anim.SetConstantPosition(sw7.Get(1),50.0, 7.0);

	anim.SetConstantPosition(sw8.Get(0),6.0, 7.0);
	anim.SetConstantPosition(sw8.Get(1),8.0, 7.0);
	anim.SetConstantPosition(sw8.Get(2),10.0, 7.0);
	anim.SetConstantPosition(sw8.Get(3),12.0, 7.0);
	anim.SetConstantPosition(sw8.Get(4),14.0, 7.0);
	anim.SetConstantPosition(sw8.Get(5),16.0, 7.0);
	anim.SetConstantPosition(sw8.Get(6),18.0, 7.0);
	anim.SetConstantPosition(sw8.Get(7),20.0, 7.0);
	
	anim.SetConstantPosition(sw9.Get(0),36.0, 12.0);
	anim.SetConstantPosition(sw9.Get(1),38.0, 12.0);
	anim.SetConstantPosition(sw9.Get(2),40.0, 12.0);
	anim.SetConstantPosition(sw9.Get(3),42.0, 12.0);
	anim.SetConstantPosition(sw9.Get(4),44.0, 12.0);
	anim.SetConstantPosition(sw9.Get(5),46.0, 12.0);
	anim.SetConstantPosition(sw9.Get(6),48.0, 12.0);
	anim.SetConstantPosition(sw9.Get(7),50.0, 12.0);
	anim.SetConstantPosition(A,26.5, 4.0);
	
	Ptr<FlowMonitor> monitor;
        FlowMonitorHelper flowmonHelper;
        monitor = flowmonHelper.InstallAll();

	Simulator::Stop (Seconds (10.0));
    	Simulator::Run ();

        double txPacketsum = 0;
        double rxPacketsum = 0;
        uint32_t DropPacketsum = 0;
        uint32_t LostPacketsum = 0;
        double Delaysum = 0;
     
     	 monitor->SerializeToXmlFile("resultsss.xml", true, true);
          monitor->CheckForLostPackets ();

          Ptr<Ipv4FlowClassifier> classifier = DynamicCast<Ipv4FlowClassifier>(flowmonHelper.GetClassifier ());

          map< FlowId, FlowMonitor::FlowStats > stats = monitor->GetFlowStats ();

          for (map<FlowId, FlowMonitor::FlowStats>::const_iterator iter = stats.begin (); iter != stats.end (); ++iter)
                {
          txPacketsum += iter->second.txPackets;
          rxPacketsum += iter->second.rxPackets;
          LostPacketsum += iter->second.lostPackets;
          DropPacketsum += iter->second.packetsDropped.size();
          Delaysum += iter->second.delaySum.GetSeconds();
          //NS_LOG_UNCOND("Tx Packets = " << iter->second.txPackets);
          //NS_LOG_UNCOND("Rx Packets = " << iter->second.rxPackets);
                }

          cout << "\n";
          cout << "\n";
          cout << "  All Tx Packets: " << txPacketsum << "\n";
          cout << "  All Rx Packets: " << rxPacketsum << "\n";
          cout << "  All Delay: " << Delaysum / txPacketsum << "\n";
          cout << "  All Lost Packets: " << LostPacketsum << "\n";
          cout << "  All Drop Packets: " << DropPacketsum << "\n";
          cout << "  Packets Delivery Ratio: " << ((rxPacketsum * 100) /txPacketsum) << "%" << "\n";
          cout << "  Packets Lost Ratio: " << ((LostPacketsum * 100) /txPacketsum) << "%" << "\n";
	  cout << "  Packets Drop Ratio: " << ((DropPacketsum * 100) /txPacketsum) << "%" << "\n";

	
	anim.SetMaxPktsPerTraceFile(20000000);
				

  	NS_LOG_INFO ("Running the Simulation.");
  	NS_LOG_INFO ("Flowmon file creating.");
  	NS_LOG_INFO ("Done.");
	Simulator::Destroy ();

	return 0;

}
