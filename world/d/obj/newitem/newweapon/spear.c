// hammer.c

#include <weapon.h>

inherit SPEAR;
inherit NEWITEM;

int is_weapon() {
    return 1;
}


void create()
{
        set_name("ǹ", ({"spear"}));
        set_weight(4000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", "����һ�ѳ�ǹ��ǹ�����Ժ��⣬");
                set("value", 500);
                set("material", "iron");
                set("wield_msg", "$N�ó�һ��$n���������С�\n");
                set("unwield_msg", "$N�������е�$n��\n");
        }

        init_spear(25);
        setup();
}
