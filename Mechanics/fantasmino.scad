$fn=50;
scale(0.5)
{

difference()
	{
	cylinder(d=60,h=10);
	translate([0,0,-1]) cylinder(d=14,h=20);
	translate([-35,0,0]) rotate([90,0,90]) scale([1,0.6,1]) cylinder(d=20,h=70);
	translate([0,35,0]) rotate([90,0,0]) scale([1,0.6,1]) cylinder(d=20,h=70);
	translate([-25,25,0]) rotate([90,0,45]) scale([1,0.6,1]) cylinder(d=20,h=70);
	translate([-25,-25,0]) rotate([90,0,135]) scale([1,0.6,1]) cylinder(d=20,h=70);

  translate([-34.5,0,0]) rotate([0,0,90]) scale([1,0.6,1]) cylinder(d=20,h=70);
  translate([0,34,0]) rotate([0,0,0]) scale([1,0.6,1]) cylinder(d=20,h=70);
  translate([0,-34,0]) rotate([0,0,0]) scale([1,0.6,1]) cylinder(d=20,h=70);
  translate([-24,24,0]) rotate([0,0,45]) scale([1,0.6,1]) cylinder(d=20,h=70);
  translate([-24,-24,0]) rotate([0,0,135]) scale([1,0.6,1]) cylinder(d=20,h=70);
	}

difference()
{
  hull()
	{
	translate([0,0,10]) cylinder(d=60,h=1);
	translate([0,0,54])sphere(d=54);
	}
  translate([-30,-10,50]) rotate([0,90,0]) scale([1,0.8,1]) cylinder(d=20,h=10);
  translate([-30,10,50]) rotate([0,90,0]) scale([1,0.8,1]) cylinder(d=20,h=10);
  translate([-34.5,0,0]) rotate([0,0,90]) scale([1,0.6,1]) cylinder(d=20,h=70);
  translate([0,34,0]) rotate([0,0,0]) scale([1,0.6,1]) cylinder(d=20,h=70);
  translate([0,-34,0]) rotate([0,0,0]) scale([1,0.6,1]) cylinder(d=20,h=70);
  translate([-24,24,0]) rotate([0,0,45]) scale([1,0.6,1]) cylinder(d=20,h=70);
  translate([-24,-24,0]) rotate([0,0,135]) scale([1,0.6,1]) cylinder(d=20,h=70);
}



translate([-22,10,50]) rotate([0,90,0])  cylinder(d=8,h=10);
translate([-22,-10,50]) rotate([0,90,0])  cylinder(d=8,h=10);

}