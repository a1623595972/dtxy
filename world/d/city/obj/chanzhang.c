// hammer.c

#include <weapon.h>

inherit STAFF;

void create()
{
        set_name("����", ({"chanzhang", "zhang", "staff"}));
        set_weight(4000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", "����һ�����ȣ����漸�������������죮\n");
                set("value", 500);
                set("material", "iron");
                set("wield_msg",
"$N�ó�һ��$n���������У�\n");
                set("unwield_msg", "$N�������е�$n��\n");
        }

	set("special_effects", "none");  // emotion
        init_staff(25);
        setup();
}
