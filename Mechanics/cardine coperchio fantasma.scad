$fn=50;
difference()
	{
	translate([-7.5,17,0]) cube([15,16,10]);
	translate([-5.5,17,-1]) cube([11,14,12]);
	translate([-8,27.5,1.8]) rotate([0,90,0]) cylinder(d=1.8,h=25);
	translate([0,-1,0])cylinder(d=40,h=11);
	translate([-3,30,6]) cube([6,6,5]);
	translate([-8,15.5,0]) rotate([45,0,0]) rotate([0,90,0]) cube([3,3,16]);
	}
difference()
{
	translate([-7.5,15,3]) cube([15,6,30]);
	translate([0,-1,0])cylinder(d=40,h=36);
	translate([0,22,4]) rotate([90,0,0]) cylinder(d=11,h=10);
	translate([0,22,18]) rotate([90,0,0]) cylinder(d=6,h=10);
	translate([-3,17,0])cube([6,6,18]);
}

difference()
{
	hull()
	{
		translate([-7.5,17,9.9]) cube([15,16,0.1]);
		difference()
		{
			translate([-7.5,15,3]) cube([15,6,30]);
			translate([0,-1,0])cylinder(d=40,h=36);
		}
	}
		translate([-5.5,17,0]) cube([11,14,34]);
		translate([0,-1,0]) cylinder(d=40,h=35);
		translate([-3,30,6]) cube([6,6,8]);
}
difference()
{
	hull()
	{
		translate([-1,21,30]) cube([2,4,1]);
		translate([-1,21,22]) cube([2,0.1,0.1]);
	}
	translate([-8,22.5,30.5]) rotate([0,90,0]) cylinder(d=1.8,h=25);
}
//difference()
//{
//	translate([0,-1.25,0])cylinder(d=44,h=20);
//	translate([0,-1.25,-1])cylinder(d=40.5,h=36);
//	translate([-7.5,17,-1]) cube([15,16,25]);
//	%translate([-24,0,10]) rotate([0,90,0]) cylinder(d=3,h=50);
//}