// Room: /d/menggu/caodui
inherit ROOM;

void create()
{
  set ("short", "��ݶ�");
  set ("long", @LONG
Į����һ�����ģ����ݶѻ��������������ڣ��ջ�ȡů��ȫƾ�ɲݣ�
���Բݶ�������ס�˵��ɹŰ�����һ���Ǹ���ª��Сé����.
LONG);

  set("outdoors", "menggu");
  set("exits", ([ /* sizeof() == 2 */
  "enter" : __DIR__"maowu",
  "west" : __DIR__"byriver",
]));
  setup();
  replace_program(ROOM);
}
