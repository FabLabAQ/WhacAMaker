$fn=50;

difference() //base
	{
	cylinder(d=35,h=10);
	translate([0,0,-1]) cylinder(d=7,h=20);
	translate([-35,0,0]) rotate([90,0,90]) scale([1,0.6,1]) cylinder(d=20,h=70);
	translate([0,35,0]) rotate([90,0,0]) scale([1,0.6,1]) cylinder(d=20,h=70);
	translate([-25,25,0]) rotate([90,0,45]) scale([1,0.6,1]) cylinder(d=20,h=70);
	translate([-25,-25,0]) rotate([90,0,135]) scale([1,0.6,1]) cylinder(d=20,h=70);

  translate([-18,0,0]) rotate([0,0,90]) scale([1,0.6,1]) cylinder(d=10,h=70);
  translate([0,19,0]) rotate([0,0,0]) scale([1,0.6,1]) cylinder(d=10,h=70);
  translate([0,-19,0]) rotate([0,0,0]) scale([1,0.6,1]) cylinder(d=10,h=70);
  translate([-13,13,0]) rotate([0,0,45]) scale([1,0.6,1]) cylinder(d=10,h=70);
  translate([-13,-13,0]) rotate([0,0,135]) scale([1,0.6,1]) cylinder(d=10,h=70);

  translate([0,6,-1]) cylinder(d=4,h=25);
  translate([0,-6,-1]) cylinder(d=4,h=25);

  translate ([0,-25,0])cube (50);
	}

difference()//body
{
  hull()
	{
	translate([0,0,10]) cylinder(d=35,h=1);
	translate([0,0,28])sphere(d=30);
	}
  translate ([0,-25,0])cube (50);
  translate([0,0,-1]) cylinder(d=7,h=22);
  translate([0,6,-1]) cylinder(d=3,h=25);
  translate([0,-6,-1]) cylinder(d=3,h=25);

  translate([-19,-10,16]) rotate([0,90,0]) cylinder(d=6.5,h=10);
  translate([-19,10,16]) rotate([0,90,0]) cylinder(d=6.5,h=10);

  translate([-18,0,0]) rotate([0,0,90]) scale([1,0.6,1]) cylinder(d=10,h=70);
  translate([0,19,0]) rotate([0,0,0]) scale([1,0.6,1]) cylinder(d=10,h=70);
  translate([0,-19,0]) rotate([0,0,0]) scale([1,0.6,1]) cylinder(d=10,h=70);
  translate([-13,13,0]) rotate([0,0,45]) scale([1,0.6,1]) cylinder(d=10,h=70);
  translate([-13,-13,0]) rotate([0,0,135]) scale([1,0.6,1]) cylinder(d=10,h=70);

//  translate([-12,6,26]) rotate([0,90,0])  cylinder(d=5.5,h=20);
//  translate([-12,-6,26]) rotate([0,90,0])  cylinder(d=5.5,h=20);
//  translate([-5,6,26]) rotate([0,90,0])  cylinder(d=7,h=20);
//  translate([-5,-6,26]) rotate([0,90,0])  cylinder(d=7,h=20);

  translate([-12,10,16]) rotate([0,90,0])  cylinder(d=3.5,h=20);
  translate([-12,-10,16]) rotate([0,90,0])  cylinder(d=3.5,h=20);
  translate([0,-6,25]) sphere(d=7);
  translate([0,6,25]) sphere(d=7);
}
