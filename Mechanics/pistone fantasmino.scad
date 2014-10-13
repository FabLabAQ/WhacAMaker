$fn=60;

difference()
	{
	cylinder (d=36.4,h=25);
	cylinder (d=6.5,h=20);
	translate([-20,-20,-7]) cube([40,40,10]);
	translate([0,0,21]) cylinder (d=31,h=6);
	translate([13,-3,0]) cube([6,6,27]);
	translate([-19,-3,0]) cube([6,6,27]);
	for(i=[0:8]) 
 { rotate([0,0,i*360/8]) translate( [0,20,14] ) sphere(r=6); }
	}


difference()
	{
	hull()
		{
		translate([-2.5,-5,20]) cube([5,10,10]);
		translate([-2.5,0,31])rotate ([0,90,0]) cylinder(d=11,h=5);
		}
	translate([-5,0,31])rotate ([0,90,0]) cylinder(d=4.7,h=10);

	}


