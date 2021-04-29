$fn=100;
$fs = 0.01;

// PCB Size Settings
pcb_w  = 30.6; // Width of PCB
pcb_l  = 37.6; // Height of PCB
pcb_hf = 7;    // Heigth of  Parts on PCB Front
pcb_hb = 6;    // Height of Parts on PCB Back

// Which Parts to Render
render_holes = true; // Create Mounting Holes in Back Cover
render_front = false;  // Render Front Part
render_back = true;   // Render Back Part

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

// Calculated Values
case_l = pcb_l+3.2;
case_w = pcb_w+3.2;
slot_len = ((case_l)/3);

rotate(a=[180,0,0]) {
// Front Part
if (render_front) {
  union() {
    difference() {
      union() {
        translate([0.8,0.8,0]) cube(size=[(pcb_l+1.6), (pcb_w+1.6), 5]);
        translate([0,0,5]) roundedcube([(case_l), case_w, (pcb_hb+pcb_hf-1.8)], false, 1, "zmax");
      }
      translate([1.6,1.6,-0.1]) cube(size=[pcb_l, pcb_w, (pcb_hb+1.7)]);
      translate([2.35,1.6,-0.1]) cube(size=[(pcb_l-1.5), pcb_w, (pcb_hf+pcb_hb+1.7)]);
      
      translate([1.6,7,-0.1]) cube(size=[pcb_l, 4, (pcb_hf+pcb_hb+1.7)]);
      translate([1.6,case_w-11,-0.1]) cube(size=[pcb_l, 4, (pcb_hf+pcb_hb+1.7)]);

      for(y=[9:+3:pcb_w-3]) {
        translate([(slot_len/3), y, pcb_hf+pcb_hb+1]) rotate(a=[45,0,0]) cube(size=[slot_len,0.8,3]);
        translate([(slot_len+(2*(slot_len/3))), y, pcb_hf+pcb_hb+1]) rotate(a=[45,0,0]) cube(size=[slot_len,0.8,3]);
      }
    }
    translate([1.6,(pcb_w/2)+4.1,pcb_hb-0.3]) rotate(a=[90,90,0]) cylinder(r=0.3,h=5);
    translate([pcb_l+1.6,(pcb_w/2)+4.1,pcb_hb-0.3]) rotate(a=[90,90,0]) cylinder(r=0.3,h=5);
  }
}

// Back Part
  if (render_back) {
    translate([0,40,0]) difference() {
      roundedcube([(case_l), case_w, 6.6], false, 1, "zmax");
      translate([0.75,0.75,0-0.1]) cube(size=[(pcb_l+1.7), (pcb_w+1.7),5.1]);
      translate([-1,case_w/2,-28.5]) rotate(a=[0,90,0]) cylinder(r=30,h=pcb_l+5);
      if (render_holes) {
        translate([case_l/5,case_w/2,4.99]) cylinder(r1=3.7,r2=1.75,h=1.62);
        translate([(case_l/5)*4,case_w/2,4.99]) cylinder(r1=3.7,r2=1.75,h=1.62);
        translate([case_l/2,7,4.99]) cylinder(r1=3.7,r2=1.75,h=1.62);
      }  
    }
  }
}
