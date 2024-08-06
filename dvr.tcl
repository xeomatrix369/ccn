#Create a simulator object
set ns [new Simulator]
$ns rtproto DV

#Define different colors for data flows (for NAM)
$ns color 1 Blue

#Open the NAM trace file
set nf [open sample.nam w]
$ns namtrace-all $nf
set tr [open sample.tr w]
$ns trace-all $tr

#Define a 'finish' procedure
proc finish {} {
    global ns nf tr
    $ns flush-trace
    #Close the NAM trace file
    close $nf
    close $tr
    #Execute NAM on the trace file
    exec nam sample.nam &
    exit 0
}

#Create four nodes
set n0 [$ns node]
set n1 [$ns node]
set n2 [$ns node]
set n3 [$ns node]

#Create links between the nodes
$ns duplex-link $n0 $n1 10Mb 10ms DropTail
$ns duplex-link $n1 $n2 10Mb 10ms DropTail
$ns duplex-link $n2 $n3 10Mb 10ms DropTail
$ns duplex-link $n3 $n0 10Mb 10ms DropTail
$ns duplex-link $n0 $n2 10Mb 10ms DropTail
$ns duplex-link $n1 $n3 10Mb 10ms DropTail

#Give node position (for NAM)
$ns duplex-link-op $n0 $n1 orient right
$ns duplex-link-op $n1 $n2 orient down
$ns duplex-link-op $n2 $n3 orient left
$ns duplex-link-op $n3 $n0 orient up
#$ns duplex-link-op $n0 $n2 orient right-down
#$ns duplex-link-op $n1 $n3 orient left-down

$ns cost $n0 $n1 1
$ns cost $n1 $n2 4
$ns cost $n2 $n3 1
$ns cost $n3 $n0 1
$ns cost $n0 $n2 2
$ns cost $n1 $n3 1

#Setup a TCP connection
set tcp [new Agent/TCP]
$tcp set class_ 1
$ns attach-agent $n1 $tcp
set sink [new Agent/TCPSink]
$ns attach-agent $n2 $sink
$ns connect $tcp $sink
$tcp set fid_ 1

#Setup a FTP over TCP connection
set ftp [new Application/FTP]
$ftp attach-agent $tcp
$ftp set type_ FTP


#Schedule events for the CBR and FTP agents
$ns at 1.0 "$ftp start"

$ns rtmodel-at 3.0 down $n1 $n2
$ns rtmodel-at 5.0 up $n1 $n2

#Call the finish procedure after 5 seconds of simulation time
$ns at 10 "finish"

#Run the simulation
$ns run
