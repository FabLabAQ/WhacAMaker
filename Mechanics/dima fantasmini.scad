$fn=60;
difference()
{
union()
{
translate([0,0,])cylinder(d=40,h=2);
translate([-5,0,0]) cube([10,30,2]);
}
translate([0,0,-1])cylinder (d=37,h=5);
}


translate([0,-19,0])cylinder (d=4,h=1.5,$fn=4);
translate([0,19,0])cylinder (d=4,h=1.5,$fn=4);
translate([19,0,0])cylinder (d=4,h=1.5,$fn=4);
translate([-19,0,0])cylinder (d=4,h=1.5,$fn=4);
