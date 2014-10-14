$fn=20;

//cube([13,55,4]);

difference()
{
hull()
	{
	cylinder(d=6,h=3);
	translate ([0,16,0]) cylinder(d=14,h=3);
	translate ([0,44,0]) cylinder(d=10,h=3);
	}

translate ([0,16,-1]) cylinder(d=7.6,h=6);
translate ([0,44,-1]) cylinder(d=5,h=6);
translate ([0,5,-1]) cylinder(d=2,h=6);
translate ([0,26,-1]) cylinder(d=2,h=6);
}
//translate ([]) cylinder(d=7,h=6);