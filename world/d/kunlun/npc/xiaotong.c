inherit NPC;
void create()
{
        set_name("小童", ({"xiao tong", "tong"}));
        set("gender", "男性" );
        set("age", 16);
        set("long", "一个可爱的小仙童。\n");
        set("class", "shen");
        set("combat_exp", 10000);
  set("daoxing", 20000);

        set("attitude", "peaceful");
        set("title", "小仙童");
        set_skill("unarmed", 40);
        set_skill("dodge", 40);
        set_skill("parry", 40);

        set("per", 20);
        set("max_kee", 200);
        setup();
        carry_object("/d/obj/cloth/xianpao")->wear();
}
void init()
{       
        object ob=this_player();
        object me=this_object();

        ::init();

        if ( ((int)ob->query("env/invisibility")  == 0) && ((string)environment(me)->query("short")==" [0;1;33m� [1m� [1m� [1m� [1m� [1m� [1m� [1m� [1m� [1m� [0m") )
        {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
}

void greeting(object ob)
{
        if( !ob || environment(ob) != environment() ) return;

        if ( (int)ob->query("combat_exp")>500000 )
                command("say 这位" + RANK_D->query_respect(ob) + "失迎了，欢迎来我们玉虚洞！\n");
        else if ( (int)ob->query("combat_exp")>100000 )
                command("say 这位" + RANK_D->query_respect(ob) + "失迎了，快请坐！欢迎来我们玉虚洞！\n");
        else if ( (int)ob->query("combat_exp")>10000 )
                command("say 这位" + RANK_D->query_respect(ob) + "，请坐！用茶！\n");
        else if ( (int)ob->query("combat_exp")>1000 )
                command("hi " + ob->query("id"));       
        else
                return;
}
