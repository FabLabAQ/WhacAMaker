$fn=30;

difference()
{
	union()
	{
		translate([5,0,0]) cube([8,40,3.5]);
		translate([57,0,0]) cube([8,40,3.5]);
	}
	hull()
	{
		translate([8.5,35,-1]) cylinder(d=3.5,h=6);
		translate([8.5,25,-1]) cylinder(d=3.5,h=6);
	}
	hull()
	{
		translate([61.5,35,-1]) cylinder(d=3.5,h=6);
		translate([61.5,25,-1]) cylinder(d=3.5,h=6);
	}

	translate([-1,-1,-1]) cube([72,20,6]);
	translate ([14,34,-1]) cube([42,26,4]);
	translate ([-1,-1,-1]) cube([6,50,4]);
	translate ([65,-1,-1]) cube([6,50,4]);
}
difference()
	{
	translate ([5,15,0]) cube([60,8,3.5]);
	translate ([20,19,-1]) cylinder(d=3,h=6);
	translate ([50,19,-1]) cylinder(d=3,h=6);
//	translate ([20,21,5]) rotate ([90,0,0]) cylinder(d=4,h=7);
//	translate ([50,21,5]) rotate ([90,0,0]) cylinder(d=4,h=7);
	}