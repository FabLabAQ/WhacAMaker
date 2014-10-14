$fn=50;

//difference()//forchetta
//	{
//	union()
//		{
//		translate([0,0,-1]) cube([3,15,12]);
//		translate([9,0,-1]) cube([3,15,12]);
//		
//		translate([0,0,5]) rotate ([0,90,0]) cylinder(d=12,h=3);
//		translate([9,0,5]) rotate ([0,90,0]) cylinder(d=12,h=3);
//		}
//	translate([-5,0,5]) rotate([0,90,0]) cylinder(d=6.5,h=20);
//	}

difference()
	{
	translate([0,0,-1]) cube([12,10,12]);
	translate([6,6,-2]) cylinder(d=4,h=14);
	}

difference()
	{
	translate([0,10,-1]) cube([12,15,12]);
	translate([6,28,5]) rotate([90,90,0]) cylinder(d=4.1,h=20);
	translate([2,18,-2]) cube([8,4,20]);
	}

