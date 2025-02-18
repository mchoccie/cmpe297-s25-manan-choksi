/*
 * SPDX-License-Identifier: GPL-2.0-only
 */

 #include "ns3/applications-module.h"
 #include "ns3/core-module.h"
 #include "ns3/internet-module.h"
 #include "ns3/network-module.h"
 #include "ns3/point-to-point-module.h"
 
 // Default Network Topology
 //
 //       10.1.1.0
 // n0 -------------- n1
 //    point-to-point
 //
 
 using namespace ns3;
 
 NS_LOG_COMPONENT_DEFINE("FirstScriptExample");
 
 int
 main(int argc, char* argv[])
 {
     uint32_t nPackets = 1;
     uint32_t PacketSize = 128;
 
     CommandLine cmd;
     cmd.AddValue("nPackets", "Number of packets to echo", nPackets);
     cmd.AddValue("PacketSize", "Size of packets", PacketSize);
     cmd.Parse(argc, argv);
 
     Time::SetResolution(Time::NS);
     LogComponentEnable("UdpEchoClientApplication", LOG_LEVEL_INFO);
     LogComponentEnable("UdpEchoServerApplication", LOG_LEVEL_INFO);
     NS_LOG_INFO("Creating Topology");
     NodeContainer nodes;
     nodes.Create(2);
 
     PointToPointHelper pointToPoint;
     // pointToPoint.SetDeviceAttribute("DataRate", StringValue("5Mbps"));
     // pointToPoint.SetChannelAttribute("Delay", StringValue("2ms"));
 
     NetDeviceContainer devices;
     devices = pointToPoint.Install(nodes);
 
     InternetStackHelper stack;
     stack.Install(nodes);
 
     Ipv4AddressHelper address;
     address.SetBase("10.1.1.0", "255.255.255.0");
 
     Ipv4InterfaceContainer interfaces = address.Assign(devices);
 
     UdpEchoServerHelper echoServer(9);
 
     ApplicationContainer serverApps = echoServer.Install(nodes.Get(1));
     serverApps.Start(Seconds(1.0));
     serverApps.Stop(Seconds(40.0));
 
     UdpEchoClientHelper echoClient(interfaces.GetAddress(1), 9);
     echoClient.SetAttribute("MaxPackets", UintegerValue(nPackets));
     // echoClient.SetAttribute("MaxPackets", UintegerValue(1));
     echoClient.SetAttribute("Interval", TimeValue(Seconds(1.0)));
     // echoClient.SetAttribute("PacketSize", UintegerValue(PacketSize));
 
     ApplicationContainer clientApps = echoClient.Install(nodes.Get(0));
     clientApps.Start(Seconds(2.0));
     clientApps.Stop(Seconds(40.0));
 
     AsciiTraceHelper ascii;
     pointToPoint.EnableAsciiAll(ascii.CreateFileStream("myfirst.tr"));
     pointToPoint.EnablePcapAll("myfirst");
     Simulator::Run();
     Simulator::Destroy();
     return 0;
 }
 