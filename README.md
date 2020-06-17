Simple Loadbalancer

Simulates communication between a browser and multiple servers. The load balancer sits in the middle of the connection and distributes 
the workload between each server so as not to cause bottlenecking. The load balancer sends/recieves the messages to each server, one 
after another.

No make file is included, to compile, run:

gcc *.c -std=c99 -o ex3_lb

