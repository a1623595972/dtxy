inherit ROOM;

void create ()
{
  set ("short", "石阶");
  set ("long", @LONG

    石阶向前延续，隐隐约约已可看见山顶云霞迷漫仙气非凡，
山顶还不时从传来阵阵诵经的声音�

�

LONG);

  set("exits", ([
        "north"   : __DIR__"lingyunge",
        "eastdown"   : __DIR__"shijie1",
      ]));
         set("outdoors", "xx" );  

  setup();
}
