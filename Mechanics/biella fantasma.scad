module forchetta()
{
difference()//forchetta
	{
	union()
		{
		translate([0,0,-1]) cube([3,15,12]);
		translate([9,0,-1]) cube([3,15,12]);
		translate([0,0,5]) rotate ([0,90,0]) cylinder(d=12,h=3);
		translate([9,0,5]) rotate ([0,90,0]) cylinder(d=12,h=3);
		}
	translate([-5,0,5]) rotate([0,90,0]) cylinder(d=6.5,h=20);
	}

	translate([0,10,-1]) cube([12,5,12]);
	
}

$fn=50;

difference() // base
	{
	translate([0,0,-1]) cube(12);
	translate([-1,6,5]) rotate([90,0,90]) cylinder(d=6.5,h=14);
	}

translate([4,12,-1]) cube ([4,78,6]); //corpo

translate([12,105,0]) rotate (180,0,0)  forchetta();