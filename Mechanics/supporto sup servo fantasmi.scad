$fn=30;

difference()
{
	union()
	{
		difference()
			{
			cube([70,40,2]);
			translate ([14,-1,-1]) cube([42,26,4]);
			}
		translate([5,0,0]) cube([9,40,3.5]);
		translate([56,0,0]) cube([9,40,3.5]);
		
//		translate([0,20,0]) cube([10,20,4]);
//		translate([60,20,0]) cube([10,20,4]);
	}
	translate([8.5,35,-1]) cylinder(d=2.5,h=6);
	translate([61.5,35,-1]) cylinder(d=2.5,h=6);
	translate([-1,-1,-1]) cube([72,4,6]);

//	translate([9,9,-1]) cylinder(d=1.5,h=6);
//	translate([9,19,-1]) cylinder(d=1.5,h=6);
//	translate([61,9,-1]) cylinder(d=1.5,h=6);
//	translate([61,19,-1]) cylinder(d=1.5,h=6);

	translate ([14,34,-1]) cube([42,26,4]);
	translate ([-1,-1,-1]) cube([6,50,4]);
	translate ([65,-1,-1]) cube([6,50,4]);
}