#include <stdio.h>

int main()
{
    printf("				<entries>\n");
    for (int i = 1; i <= 49; i++) {
        printf("\t\t\t<tag type=\"pic1\" name=\"comp%02d\" userdata=\"\">\n"
               "\t\t\t\t<visible>01</visible>\n"
               "\t\t\t\t<WidescreenAffected>00</WidescreenAffected>\n"
               "\t\t\t\t<flag>00</flag>\n"
               "\t\t\t\t<origin x=\"Left\" y=\"Top\" />\n"
               "\t\t\t\t<alpha>ff</alpha>\n"
               "\t\t\t\t<padding>00</padding>\n"
               "\t\t\t\t<translate>\n"
               "\t\t\t\t\t<x>-150.0000000000000000000000000</x>\n"
               "\t\t\t\t\t<y>-200.0000000000000000000000000</y>\n"
               "\t\t\t\t\t<z>0.0000000000000000000000000</z>\n"
               "\t\t\t\t</translate>\n"
               "\t\t\t\t<rotate>\n"
               "\t\t\t\t\t<x>0.00000000000000000000</x>\n"
               "\t\t\t\t\t<y>0.00000000000000000000</y>\n"
               "\t\t\t\t\t<z>0.00000000000000000000</z>\n"
               "\t\t\t\t</rotate>\n"
               "\t\t\t\t<scale>\n"
               "\t\t\t\t\t<x>0.5000000000</x>\n"
               "\t\t\t\t\t<y>0.6000000238</y>\n"
               "\t\t\t\t</scale>\n"
               "\t\t\t\t<size>\n"
               "\t\t\t\t\t<width>276.000000</width>\n"
               "\t\t\t\t\t<height>59.000000</height>\n"
               "\t\t\t\t</size>\n"
               "\t\t\t\t<material name=\"comp%02d\" />\n"
               "\t\t\t\t<colors>\n"
               "\t\t\t\t\t<vtxColorTL r=\"ff\" g=\"ff\" b=\"ff\" a=\"ff\" />\n"
               "\t\t\t\t\t<vtxColorTR r=\"ff\" g=\"ff\" b=\"ff\" a=\"ff\" />\n"
               "\t\t\t\t\t<vtxColorBL r=\"ff\" g=\"ff\" b=\"ff\" a=\"ff\" />\n"
               "\t\t\t\t\t<vtxColorBR r=\"ff\" g=\"ff\" b=\"ff\" a=\"ff\" />\n"
               "\t\t\t\t</colors>\n"
               "\t\t\t\t<coordinates>\n"
               "\t\t\t\t\t<set>\n"
               "\t\t\t\t\t\t<coordTL s=\"0.000000\" t=\"0.000000\" />\n"
               "\t\t\t\t\t\t<coordTR s=\"1.000000\" t=\"0.000000\" />\n"
               "\t\t\t\t\t\t<coordBL s=\"0.000000\" t=\"1.000000\" />\n"
               "\t\t\t\t\t\t<coordBR s=\"1.000000\" t=\"1.000000\" />\n"
               "\t\t\t\t\t</set>\n"
               "\t\t\t\t</coordinates>\n"
               "\t\t\t</tag>\n", i, i);
    }
    return 0;
}