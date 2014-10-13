$fn=30;
translate([0,-5,0])
difference()
{
cube ([20,10,3]);
translate([10,5,-1]) cylinder(d=4,h=5);
}
difference()
{
	union()
		{
		cube ([2,20,10]);
		translate([-2,10,0]) cube ([2,10,10]);
		}
	translate([-4,15,5]) rotate ([0,90,0]) cylinder(d=3.5,h=7);
	translate([-3,-1,3]) rotate ([25,0,0]) cube([6,20,10]);
}

difference()
{
	union()
		{
		translate([18,0,0]) cube ([2,20,10]);
		translate([20,10,0]) cube ([2,10,10]);
		}
	translate([16,15,5]) rotate ([0,90,0]) cylinder(d=3.5,h=7);
	translate([17,-1,3]) rotate ([25,0,0]) cube([6,20,10]);
}
