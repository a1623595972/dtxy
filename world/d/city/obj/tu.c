//Cracked by Roath
inherit ITEM;
#include <ansi.h>

int do_locate(string arg);
int do_task();

void create()
{
        set_name(HIW"̽��"HIG"ͼ"NOR, ({"tanbao tu","tu"}));
        set_weight(80);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "����һ������Ѱ�Ҷ�ʧ�����̽��ͼ�������зǷ���ħ����\n"+
                            "����(locate)�����ҵ���Ʒ�Ĵ��λ�ã�(task)\n");
                set("unit", "��");
                set("value", 300);
        }
	set("special_effects", "none");  // emotion
}

void init()
{
   object ob = this_player();
   add_action("do_locate","locate");
  add_action("do_task","task");
}

int do_task()
{
   string output;
   output="̽��ͼ��ͻȻӳ�ֳ�һƪӬͷС�֣�\n\n"+"/adm/daemons/questd"->dyn_quest_list();
   this_player()->start_more(output);
   return 1;
}

int query_autoload() { return 1; }

int do_locate(string arg)
{
   if ( ! arg)

   return notify_fail("locate <��Ʒ>\n");
   else
   if (this_player()->query("sen") < 15)
   return notify_fail("��ķ��������ˡ�\n");
   else
   "/adm/daemons/questd"->locate_quest(this_player(),arg);
   this_player()->add("sen",-5);
   return 1;
}
