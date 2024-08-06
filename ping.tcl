# Initialize NS simulator, trace files, and node creation
set ns [new Simulator]
set tf [open lab2.tr w]
$ns trace-all $tf
set nf [open lab2.nam w]
$ns namtrace-all $nf

# Define colors for nodes
$ns color 1 "red"
$ns color 2 "green"

# Create nodes
set n0 [$ns node]
set n1 [$ns node]
set n2 [$ns node]
set n3 [$ns node]
set n4 [$ns node]
set n5 [$ns node]
set n6 [$ns node]

# Set labels for nodes
$n0 label "Ping0"
$n4 label "Ping4"
$n5 label "Ping5"
$n6 label "Ping6"
$n2 label "Router"

# Create duplex links between nodes
$ns duplex-link $n0 $n2 100Mb 300ms DropTail
$ns duplex-link $n1 $n2 1Mb 300ms DropTail
$ns duplex-link $n3 $n2 1Mb 300ms DropTail
$ns duplex-link $n5 $n2 100Mb 300ms DropTail
$ns duplex-link $n2 $n4 1Mb 300ms DropTail
$ns duplex-link $n2 $n6 1Mb 300ms DropTail

# Set queue limits
$ns queue-limit $n0 $n2 5
$ns queue-limit $n2 $n4 3
$ns queue-limit $n2 $n6 2
$ns queue-limit $n5 $n2 5

# Create ping agents and attach to nodes
set ping0 [new Agent/Ping]
$ns attach-agent $n0 $ping0
set ping4 [new Agent/Ping]
$ns attach-agent $n4 $ping4
set ping5 [new Agent/Ping]
$ns attach-agent $n5 $ping5
set ping6 [new Agent/Ping]
$ns attach-agent $n6 $ping6

# Set parameters for ping agents
$ping0 set packetSize_ 50000
$ping0 set interval_ 0.0001
$ping5 set packetSize_ 60000
$ping5 set interval_ 0.00001
$ping0 set class_ 1
$ping5 set class_ 2

# Define a 'recv' function for the class 'Agent/Ping'
Agent/Ping instproc recv {from rtt} {
    $self instvar node_
    global dropped_packets_due_to_congestion

    puts "The node [$node_ id] received a reply from $from with round trip time of $rtt"
    
    # Check if packet was dropped due to congestion (adjust condition as per your logic)
    if {$rtt > 0.1} {
        # Increment dropped packets due to congestion
        incr dropped_packets_due_to_congestion
    }
}

# Schedule events for ping agents
for {set i 1} {$i <= 10} {incr i} {
    $ns at [expr {$i * 0.1}] "$ping0 send"
    $ns at [expr {$i * 0.1}] "$ping5 send"
}

# Function to finish simulation and print dropped packets count
proc finish {} {
    global ns nf tf dropped_packets_due_to_congestion
    exec nam lab2.nam &
    $ns flush-trace
    close $tf
    close $nf
    puts "Total packets dropped due to congestion: $dropped_packets_due_to_congestion"
    exit 0
}

# Schedule simulation end
$ns at 5.0 "finish"

# Run the simulation
$ns run

