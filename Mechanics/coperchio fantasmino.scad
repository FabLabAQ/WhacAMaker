$fn=60;

translate([0,-1,0])cylinder (d=40,h=2);
translate([-5,0,0]) cube([10,25,2]);
difference() //cardine
	{
	translate([-5,23,0]) cube([10,7,4]); 
	translate([-6,27.5,1.8]) rotate([0,90,0]) cylinder(d=1.8,h=12);
	translate([-6,30,0]) rotate([0,90,0]) cylinder(d=2,h=12,$fn=4);
	}

difference() //reggimolla
	{
	translate([-3,21,2]) cube([6,6,7]);
	translate([0,24,4]) cylinder(d=1.9,h=7);
	translate([-6,27.5,1.8]) rotate([0,90,0]) cylinder(d=1.8,h=12);
	}
	
//hull()
//	{
//	translate([-1,10,9]) cube([2,3,1]);//punta
//	translate([-1.5,-15,0]) cube([3,30,1]);//base
//	}
