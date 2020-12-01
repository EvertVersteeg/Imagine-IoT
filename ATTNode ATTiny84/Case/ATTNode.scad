$fn=100;

translate([5,43.5,50])rotate(a=[270,0,270]) union() {
  difference() {
  minkowski() {
    cube(size=[36,48,16]);
    translate([1,1,0]) sphere(2);
  }
  translate([1,1,6]) cube(size=[36,48,16]);
  translate([1,5.6,1]) cube(size=[36,41.5,16]);
  for(y=[20:+3:40]) {
    translate([9.5,y,-5]) rotate(a=[-45,0,0]) cube(size=[9,0.9,10]);
    translate([20,y,-5]) rotate(a=[-45,0,0]) cube(size=[9,0.9,10]);
  }
  translate([0.55,-1.5,14.5]) cube(size=[37.1,51.6,1]);
  translate([1,-1.5,15.4]) cube(size=[36,51,1.2]);
  translate([-4,-4,16.5]) cube(size=[60,60,2]);
}
translate([14.5,0.1,13.7]) rotate(a=[45,0,0]) cube(size=[9,1,1]);
}

translate([25,0,0]) difference() {
  union() {
    translate([0.2,0,0]) cube(size=[36.6,50.5,0.8]);
    translate([0.6,0,0.8]) cube(size=[35.8,50,1.2]);
  }
  translate([13.5,0.7,-0.8]) rotate(a=[45,0,0]) cube(size=[10,1.5,1.1]);
  translate([7,10,-2]) cylinder(r=1.75,h=5);
  translate([7,10,-0.1]) cylinder(r1=3.5,r2=1.75,h=1.4);
  translate([29.5,40,-2]) cylinder(r=1.75,h=5);
  translate([29.5,40,-0.1]) cylinder(r1=3.7,r2=1.75,h=1.4);
  translate([0,49,-1]) rotate(a=[0,0,60]) cube(size=[2,2,4]);
  translate([37,49,-1]) rotate(a=[0,0,30]) cube(size=[2,2,4]);
}
