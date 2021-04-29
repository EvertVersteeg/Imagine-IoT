$fn=100;
$fs = 0.01;

module roundedcube(size = [1, 1, 1], center = false, radius = 0.5, apply_to = "all") {
	// If single value, convert to [x, y, z] vector
	size = (size[0] == undef) ? [size, size, size] : size;

	translate_min = radius;
	translate_xmax = size[0] - radius;
	translate_ymax = size[1] - radius;
	translate_zmax = size[2] - radius;

	diameter = radius * 2;

	module build_point(type = "sphere", rotate = [0, 0, 0]) {
		if (type == "sphere") {
			sphere(r = radius);
		} else if (type == "cylinder") {
			rotate(a = rotate)
			cylinder(h = diameter, r = radius, center = true);
		}
	}

	obj_translate = (center == false) ?
		[0, 0, 0] : [
			-(size[0] / 2),
			-(size[1] / 2),
			-(size[2] / 2)
		];

	translate(v = obj_translate) {
		hull() {
			for (translate_x = [translate_min, translate_xmax]) {
				x_at = (translate_x == translate_min) ? "min" : "max";
				for (translate_y = [translate_min, translate_ymax]) {
					y_at = (translate_y == translate_min) ? "min" : "max";
					for (translate_z = [translate_min, translate_zmax]) {
						z_at = (translate_z == translate_min) ? "min" : "max";

						translate(v = [translate_x, translate_y, translate_z])
						if (
							(apply_to == "all") ||
							(apply_to == "xmin" && x_at == "min") || (apply_to == "xmax" && x_at == "max") ||
							(apply_to == "ymin" && y_at == "min") || (apply_to == "ymax" && y_at == "max") ||
							(apply_to == "zmin" && z_at == "min") || (apply_to == "zmax" && z_at == "max")
						) {
							build_point("sphere");
						} else {
							rotate = 
								(apply_to == "xmin" || apply_to == "xmax" || apply_to == "x") ? [0, 90, 0] : (
								(apply_to == "ymin" || apply_to == "ymax" || apply_to == "y") ? [90, 90, 0] :
								[0, 0, 0]
							);
							build_point("cylinder", rotate);
						}
					}
				}
			}
		}
	}
}


rotate(a=[180,0,0]) {
// Front Part
union() {
  difference() {
    union() {
      translate([0.8,0.8,0]) cube(size=[35.6,27.8,5]);
      translate([0,0,5]) roundedcube([37.2,29.4,9.5], false, 1, "zmax");
    }
    translate([1.6,1.6,-0.1]) cube(size=[34,26.2,7.3]);
    translate([1.6,2.6,-0.1]) cube(size=[34,24.2,13]);
    translate([1.6,1.6,-0.1]) cube(size=[6,26.2,13]);
    for(y=[9:+3:25]) {
      translate([5.6,y,12.3]) rotate(a=[45,0,0]) cube(size=[12,0.8,3]);
      translate([19.6,y,12.3]) rotate(a=[45,0,0]) cube(size=[12,0.8,3]);
    }
  }
  translate([16.1,1.6,5.3]) rotate(a=[0,90,0]) cylinder(r=0.3,h=5);
  translate([16.1,27.8,5.3]) rotate(a=[0,90,0]) cylinder(r=0.3,h=5);
}

// Back Part
translate([0,40,0]) difference() {
  roundedcube([37.2,29.4,8.6], false, 1, "zmax");
  translate([0.75,0.75,0-0.1]) cube(size=[35.7,27.9,5.1]);
  translate([1.6,1.6,-0.1]) cube(size=[34,26.2,7.1]);
  // Mounting Holes Start
  translate([7,14.7,7]) cylinder(r1=3.7,r2=1.75,h=1.6);
  translate([30.2,14.7,7]) cylinder(r1=3.7,r2=1.75,h=1.6);
  translate([18.6,7,7]) cylinder(r1=3.7,r2=1.75,h=1.6);
  // Mounting Holes End
  translate([-1,14.7,-28.5]) rotate(a=[0,90,0]) cylinder(r=30,h=39);
}
}