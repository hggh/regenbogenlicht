use <hggh/mico_usb_breakout_holder.scad>


BOX_SIZE_X = 85;
BOX_SIZE_Y = 60;
BOX_SIZE_Z = 50;

module conn() {
    rotate([0, 90, 0]) cylinder(d=3, h=20, $fn=200);
}

difference() {
    cube([BOX_SIZE_X, BOX_SIZE_Y, BOX_SIZE_Z]);
    translate([2, (BOX_SIZE_Y - 35)/2, -1]) {
        cube([5, 35, 200]);
    }
    translate([2, 2, -2]) {
        cube([BOX_SIZE_X -4 , BOX_SIZE_Y-4, BOX_SIZE_Z]);
    }
    translate([BOX_SIZE_X-25, BOX_SIZE_Y/2, 0]) {
        cylinder(d=8, h=200, $fn=200);
    }
    translate([-1, (BOX_SIZE_Y - 35)/2, 0]) {
        translate([0, 7.5, 10]) conn();
        translate([0, 7.5, 26.5]) conn();
        translate([0, 7.5, 41.5]) conn();
        
        translate([0, 17.5, 26.5]) conn();
        
        translate([0, 27.5, 10]) conn();
        translate([0, 27.5, 26.5]) conn();
        translate([0, 27.5, 41.5]) conn();
    }
    translate([-1, 2, 19]) {
        cube([20, 7, 15]);
    }
}
translate([2.1, 8, 20]) {
    rotate([90, 0,0]) mico_usb_breakout_holder();
}