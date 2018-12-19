#if 0
import math

# base coordinates 
def coodinateAt(r, theta, Ox = 0, Oy = 0, Oz = 0):
   x = Ox + (r*math.cos(math.radians(theta))); 
   y = Oy + (r*math.sin(math.radians(theta)));
   return rf.Vector3(x, y, Oz);

# custom range
def my_range(start, end, step):
    if start <= end:
        # increasing order
        while start < end:
            yield start;
            start += step;

    # decreasing order
    while start >= end:
        yield start;
        start -= step;    

# get the unit-normal
def getNormal(a, b, c):
    crs = (b - a).cross(c - a); # from origin
    return crs.normalize();

# get calling form
form = rf.form.appContext.getCallingForm()
# get objects
objs = form.getObjs()
# process all objects
for obj in objs:
  if obj == None:
    continue
  if obj.getClassName() != "YAMSBodyProto":
    continue
  with obj.openBuilder() as geoBuilder:
    # Material
    geoBuilder.mtlAmbientColor(0, 0, 1)
    geoBuilder.mtlDiffuseColor(0, 0, 1)
    geoBuilder.mtlSpecularColor(.8, .8, .8)
    geoBuilder.mtlAlpha(0.5)
    geoBuilder.mtlShininess(64)
    geoBuilder.material("blue")
    
    # GState
    geoBuilder.gsFrontMaterial("blue")
    geoBuilder.gsFront(True)
    geoBuilder.gsLighting(True)
    geoBuilder.gState("blue")
    
    # Material
    geoBuilder.mtlAmbientColor(.2, .2, .2)
    geoBuilder.mtlDiffuseColor(.8, .8, .8)
    geoBuilder.mtlSpecularColor(.8, .8, .8)
    geoBuilder.mtlAlpha(1.0)
    geoBuilder.mtlShininess(64)
    geoBuilder.material("white")
    
    # Texture
    geoBuilder.texFilePath("StrikeOut.png")
    geoBuilder.texMagFilter(rf.yams.ofm.FilterMode.Linear)
    geoBuilder.texMinFilter(rf.yams.ofm.FilterMode.Nearest)
    geoBuilder.texture("StrikeOut")
    
    # GState
    geoBuilder.gsFrontMaterial("white")
    geoBuilder.gsTexture("StrikeOut")
    geoBuilder.gsFront(True)
    geoBuilder.gsLighting(True)
    geoBuilder.gState("white-textured")
    
    # Parameters of geometry
    bO = rf.Vector3(0, 0, 0); # bO - origin/ center of the cone base
    a =  rf.Vector3(0, 0, 3); # a - position of apex
    r = 2;                    # r - radius of directrix
    n = 360;                  # n - no. of total line of faces
    triangles = 100;           # triangles - no. triangles for constructing the faces
    triangles = 6 if triangles < 6 else triangles;

    geoBuilder.primType(rf.yams.ofm.PrimType.Triangles);

    # list of angles
    theta_list = [];
    # geoBuilder.normal(d.x(), d.y(), d.z());
    for theta in my_range(0, n, n/triangles):
        if theta != n: 
            theta_list.append(theta);
    for index in range(3):     # repeat the first three again
        theta_list.append(theta_list[index]);
        
    geoBuilder.useGState("blue");
    # Geometry
    for index in range(len(theta_list[:-3])):
        theta0 = theta_list[index];
        theta1 = theta_list[index+1];
        theta2 = theta_list[index+2];
        theta3 = theta_list[index+3];

    # Base
        geoBuilder.vertexType(True, False, True);
        vtx1 = coodinateAt(r, theta1, bO.x(), bO.y(), bO.z());
        vtx2 = coodinateAt(r, theta0, bO.x(), bO.y(), bO.z());
        crs = (vtx1 - bO).cross(vtx2-vtx1); # from origin
        nrml = crs.normalize();  

        geoBuilder.normal(nrml.x(), nrml.y(), nrml.z());
        geoBuilder.vertex(bO.x(), bO.y(), bO.z());
        geoBuilder.vertex(vtx1.x(), vtx1.y(), vtx1.z());
        geoBuilder.vertex(vtx2.x(), vtx2.y(), vtx2.z());

   # Surface
        geoBuilder.vertexType(True, False, False);

        vtx1 = coodinateAt(r, theta0, bO.x(), bO.y(), bO.z());
        vtx2 = coodinateAt(r, theta1, bO.x(), bO.y(), bO.z());
        vtx4 = coodinateAt(r, theta2, bO.x(), bO.y(), bO.z());
        vtx6 = coodinateAt(r, theta3, bO.x(), bO.y(), bO.z());
    
        nrml_20 = getNormal(vtx2, a, vtx1); # 1b - 2b - a
        nrml_21 = getNormal(vtx2, vtx4, a); # 2b - 4b - a
        nrml_40 = getNormal(vtx4, a, vtx2); # 2b - 4b - a
        nrml_41 = getNormal(vtx4, vtx6, a); # 4b - 6b - a

        nrml1 = (nrml_20 + nrml_21).normalize();
        nrml2 = (nrml_40 + nrml_41).normalize();
        nrml3 = getNormal(a, vtx2, vtx4);   # 2b - 4b - a

        geoBuilder.normal(nrml1.x(), nrml1.y(), nrml1.z());
        geoBuilder.vertex(vtx2.x(), vtx2.y(), vtx2.z());

        geoBuilder.normal(nrml2.x(), nrml2.y(), nrml2.z());
        geoBuilder.vertex(vtx4.x(), vtx4.y(), vtx4.z());

        geoBuilder.normal(nrml3.x(), nrml3.y(), nrml3.z());
        geoBuilder.vertex(a.x(), a.y(), a.z());
#endif