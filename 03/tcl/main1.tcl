while {1} {
    lassign [lsort -integer [regexp -all -inline {\S+} [gets stdin]]] a b c
    if {$a == {}} {puts $t; exit}
    incr t [expr {$c < $a + $b}]
}
