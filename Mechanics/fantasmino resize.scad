$fn=50;

difference()
	{
	cylinder(d=35,h=10);
	translate([0,0,-1]) cylinder(d=7,h=20);
	translate([-35,0,0]) rotate([90,0,90]) scale([1,0.6,1]) cylinder(d=20,h=70);
	translate([0,35,0]) rotate([90,0,0]) scale([1,0.6,1]) cylinder(d=20,h=70);
	translate([-25,25,0]) rotate([90,0,45]) scale([1,0.6,1]) cylinder(d=20,h=70);
	translate([-25,-25,0]) rotate([90,0,135]) scale([1,0.6,1]) cylinder(d=20,h=70);

  translate([-19,0,0]) rotate([0,0,90]) scale([1,0.6,1]) cylinder(d=10,h=70);
  translate([0,19,0]) rotate([0,0,0]) scale([1,0.6,1]) cylinder(d=10,h=70);
  translate([0,-19,0]) rotate([0,0,0]) scale([1,0.6,1]) cylinder(d=10,h=70);
  translate([-14,14,0]) rotate([0,0,45]) scale([1,0.6,1]) cylinder(d=10,h=70);
  translate([-14,-14,0]) rotate([0,0,135]) scale([1,0.6,1]) cylinder(d=10,h=70);
  translate ([0,-25,0])cube (50);
	}

difference()
{
  hull()
	{
	translate([0,0,10]) cylinder(d=35,h=1);
	translate([0,0,28])sphere(d=30);
	}
  translate ([0,-25,0])cube (50);
  translate([0,0,-1]) cylinder(d=7,h=25);
  translate([-20,-6,26]) rotate([0,90,0]) scale([1,0.8,1]) cylinder(d=10,h=10);
  translate([-20,6,26]) rotate([0,90,0]) scale([1,0.8,1]) cylinder(d=10,h=10);

  translate([-19,0,0]) rotate([0,0,90]) scale([1,0.6,1]) cylinder(d=10,h=70);
  translate([0,19,0]) rotate([0,0,0]) scale([1,0.6,1]) cylinder(d=10,h=70);
  translate([0,-19,0]) rotate([0,0,0]) scale([1,0.6,1]) cylinder(d=10,h=70);
  translate([-14,14,0]) rotate([0,0,45]) scale([1,0.6,1]) cylinder(d=10,h=70);
  translate([-14,-14,0]) rotate([0,0,135]) scale([1,0.6,1]) cylinder(d=10,h=70);
}

translate([-12,6,26]) rotate([0,90,0])  cylinder(d=4,h=10);
translate([-12,-6,26]) rotate([0,90,0])  cylinder(d=4,h=10);


//translate ([0,-25,0])cube (50);