while {1} {
    lassign [regexp -all -inline {\S+} [gets stdin]] a0 b0 c0
    lassign [regexp -all -inline {\S+} [gets stdin]] a1 b1 c1
    lassign [regexp -all -inline {\S+} [gets stdin]] a2 b2 c2
    if {$a0 == {}} {puts $t; exit}
    
    lassign [lsort -integer [list $a0 $a1 $a2]] a0 a1 a2
    lassign [lsort -integer [list $b0 $b1 $b2]] b0 b1 b2
    lassign [lsort -integer [list $c0 $c1 $c2]] c0 c1 c2
    incr t [expr {$a2 < $a0 + $a1}]
    incr t [expr {$b2 < $b0 + $b1}]
    incr t [expr {$c2 < $c0 + $c1}]
}
