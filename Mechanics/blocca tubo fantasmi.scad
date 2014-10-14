$fn=50;

difference()
{
	union()
	{
		translate([-7.5,-35,0]) cube([15,70,2.5]);
		translate([-7.5,-23,0]) cube([15,46,15]);
		cylinder(d=44,h=13);
	}
	translate([0,0,-0.5])cylinder(d=41.3,h=22);
	translate([0,-29,-1])cylinder(d=3,h=5);
	translate([0,29,-1])cylinder(d=3,h=5);
	translate([0,25,10]) rotate([90,0,0]) cylinder(d=3,h=50);
	translate([15,-8.6,-1]) cube(17.2);
}
