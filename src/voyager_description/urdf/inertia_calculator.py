#!/usr/bin/env python

import math

class InertialCalculator(object):

    def __init__(self):
        print("URDF Inertial Calculator Initialised...")

    def start_ask_loop(self):
        selection = "START"
        while selection.upper() != "Q":  # accept 'q' as well
            print("#############################")
            print("Select Geometry to Calculate:")
            print("[1] Box width(w) * depth(d) * height(h)")
            print("[2] Sphere radius(r)")
            print("[3] Cylinder radius(r) * height(h)")
            print("[Q] END program")
            selection = input(">>")
            self.select_action(selection)

        print("URDF Inertial Calculator Quit...Thank you")

    def select_action(self, selection):
        if selection == "1":
            try:
                mass = float(input("mass>>"))
                width = float(input("width>>"))
                depth = float(input("depth>>"))
                height = float(input("height>>"))
                self.calculate_box_inertia(m=mass, w=width, d=depth, h=height)
            except ValueError:
                print("Invalid input. Please enter numeric values.")
        elif selection == "2":
            try:
                mass = float(input("mass>>"))
                radius = float(input("radius>>"))
                self.calculate_sphere_inertia(m=mass, r=radius)
            except ValueError:
                print("Invalid input. Please enter numeric values.")
        elif selection == "3":
            try:
                mass = float(input("mass>>"))
                radius = float(input("radius>>"))
                height = float(input("height>>"))
                self.calculate_cylinder_inertia(m=mass, r=radius, h=height)
            except ValueError:
                print("Invalid input. Please enter numeric values.")
        elif selection.upper() == "Q":  # accept 'q' as well
            print("Selected Quit")
        else:
            print("Usage: Select one of the given options")

    def calculate_box_inertia(self, m, w, d, h):
        Iw = (m / 12.0) * (d ** 2 + h ** 2)
        Id = (m / 12.0) * (w ** 2 + h ** 2)
        Ih = (m / 12.0) * (w ** 2 + d ** 2)
        print(f'BOX w*d*h, need to define which axes are which for ixx, iyy, and izz')
        print(f'Iw="{Iw}" Id="{Id}" Ih="{Ih}" ixy="0.0" ixz="0.0" iyz="0.0"')

    def calculate_sphere_inertia(self, m, r):
        I = (2 * m * r ** 2) / 5.0
        print(f'SPHERE ixx="{I}" ixy="0.0" ixz="0.0" iyy="{I}" iyz="0.0" izz="{I}"')

    def calculate_cylinder_inertia(self, m, r, h):
        Ix = (m / 12.0) * (3 * r ** 2 + h ** 2)
        Iy = Ix
        Iz = (m * r ** 2) / 2.0
        print(f'Cylinder ixx="{Ix}" ixy="0.0" ixz="0.0" iyy="{Iy}" iyz="0.0" izz="{Iz}"')

if __name__ == "__main__":
    inertial_object = InertialCalculator()
    inertial_object.start_ask_loop()
