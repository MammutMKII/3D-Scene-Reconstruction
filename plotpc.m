[x,y,z] = import_pc_data();
tri = delaunay(x,y);
hold on
plt = trisurf(tri,x,-y,z);
alpha 0.4
hold off
axis vis3d