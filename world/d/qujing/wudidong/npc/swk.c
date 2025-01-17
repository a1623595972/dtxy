// demongorgon.c

#include <ansi.h>

inherit NPC;

void create()
{
	set_name( HIW "孙悟空" NOR, ({ "sun xingzhe","swk","sun","xinzhe" }) );
	set("long",
		"一个身不足五尺，瘦瘦干干，满身黄毛的猢狲。\n");

	set("age", 30);
        set("title", HIY"大徒弟"NOR);
	set("max_gin", 3000);
	set("max_kee", 3000);
	set("max_sen", 3000);

	set("max_atman", 3000);
	set("atman", 3000);
      set("max_force", 5000);
      set("force", 10000);
      set("max_mana", 5000);
      set("mana", 10000);

	set("str", 40);
	set("cor", 40);
	set("cps", 40);
	set("spi", 40);
	set("int", 40);
	set("con", 40);
	set("kar", 40);
	set("per", 10);

	set("combat_exp", 3500000);
	set("daoxing", 2000000);

	set_skill("unarmed", 250+random(50));
        set_skill("dodge", 250+random(50));
        set_skill("parry", 250+random(50));
	set_skill("stick", 250+random(50));
	set_skill("spells", 250+random(50));
	set_skill("dao", 250+random(50));
	set_skill("puti-zhi", 250+random(50));
	set_skill("wuxiangforce", 250+random(50));
	set_skill("force", 250+random(50));
	set_skill("qianjun-bang", 250+random(50));
	set_skill("jindouyun", 250+random(50));
	
	map_skill("spells", "dao");
	map_skill("unarmed", "puti-zhi");
	map_skill("force", "wuxiangforce");
	map_skill("stick", "qianjun-bang");
	map_skill("parry", "qianjun-bang");
	map_skill("dodge", "jindouyun");
        set("force_factor",300);	
        set("mana_factor",300);
        set("bellicosity",300);
        set("nk_gain", 100+random(50));
        set("nk_factor", 12);

	set("chat_chance_combat", 80);
        set("chat_msg_combat", ({
		(: cast_spell, "light" :),
		(: cast_spell, "dingshen" :),
                (: cast_spell, "thunder" :)
        }) );

	set_temp("apply/attack", 200);
	set_temp("apply/defense", 200);
	set_temp("apply/armor", 250);
	set_temp("apply/damage", 250);

	setup();

        carry_object("/d/obj/weapon/stick/fake-jingubang")->wield(); 
        carry_object("/obj/cloth")->wear();
        carry_object("/d/obj/drug/jinchuang");
        carry_object("/d/obj/drug/jinchuang");
        carry_object("/d/obj/drug/jinchuang");
        carry_object("/d/obj/drug/jinchuang");
        carry_object("/d/obj/drug/jinchuang");
        carry_object("/d/obj/drug/jinchuang");
        carry_object("/d/obj/drug/jinchuang");
        carry_object("/d/obj/drug/jinchuang");
        carry_object("/d/obj/drug/jinchuang");
        carry_object("/d/obj/drug/jinchuang");
        carry_object("/d/obj/drug/jinchuang");
        carry_object("/d/obj/drug/jinchuang");
}


void init()
{
  ::init();
  call_out("leave",180);   
}

void leave()
{
      	object me = this_object(); 
      	object who = me->query("owner");
      	if( me->is_fighting() )
   		return;
	if( who )
	{
		if( who->query_temp("daojian/swk") == "begin" )
		{
			message("system",HIW"【"+HIR+"西天取经"+HIW+"】"+HIY+"玉鼠"+NOR"："+who->name()+"到现在还不能赶走孙悟空，看来没希望了！\n"NOR,users());
			message("system",HIW"【"+HIR+"西天取经"+HIW+"】"+HIY+"玉鼠"+NOR"：小的们，把唐僧他们送出去吧，也好保我们一时平安！\n"NOR,users());
			message("system",HIW"【"+HIR+"西天取经"+HIW+"】"+HIY+"悟空"+NOR"：算你们识相，师傅说上天有好生之德，今日就放过你们！\n"NOR,users());
			message("system",HIW"【"+HIR+"西天取经"+HIW+"】"+HIY+"唐僧"+NOR"：悟空佛法大有长进啊，你们以后莫要为害。徒弟们，我们上路吧！\n"NOR,users());
			who->set_temp("daojian/swk","fail");
		}
		if( who->query_temp("daojian/ts") == "begin" )
        	{
	        	who->set_temp("daojian/ts","fail");
	        	message("system",HIW"【"+HIR+"西天取经"+HIW+"】"+HIY+"悟空"+NOR"：师傅妖怪都被我吓跑了，我们上路吧！师徒四人匆匆向西天赶去！\n"NOR,users());
        	}
		if( who->query_temp("daojian/lijing") == "begin" )
		{
			message("system",HIW"【"+HIR+"西天取经"+HIW+"】"+HIY+"玉鼠"+NOR"："+who->name()+"到现在还不能赶走李靖，看来没希望了！\n"NOR,users());
			message("system",HIW"【"+HIR+"西天取经"+HIW+"】"+HIY+"玉鼠"+NOR"：小的们，把唐僧他们送出去吧，也好保我们一时平安！\n"NOR,users());
			message("system",HIW"【"+HIR+"西天取经"+HIW+"】"+HIY+"悟空"+NOR"：算你们识相，师傅说上天有好生之德，今日就放过你们！\n"NOR,users());
			message("system",HIW"【"+HIR+"西天取经"+HIW+"】"+HIY+"唐僧"+NOR"：悟空佛法大有长进啊，多谢李天王，哪吒三太子。徒弟们，我们上路吧！\n"NOR,users());
			who->set_temp("daojian/lijing","fail");
		}
	}
   	remove_call_out("leave");
        destruct(this_object());
}

void die ()
{
        object me = this_object();
        object who = me->query("owner");
        if( query_temp("last_damage_from") == who )
        {
        	if( who->query_temp("daojian/ts") == "begin" )
        	{
	        	who->set_temp("daojian/ts","done");
	        	message("system",HIW"【"+HIR+"西天取经"+HIW+"】"+HIY+"唐僧"+NOR"：“啊”～～～！\n"NOR,users());
	        	message("system",HIW"【"+HIR+"西天取经"+HIW+"】"+HIY+"沙僧"+NOR"：“啊”～～～！\n"NOR,users());
	        	message("system",HIW"【"+HIR+"西天取经"+HIW+"】"+HIY+"悟空"+NOR"：大怒：妖怪好狡猾，竟然调虎离山。孙悟空架起筋斗云往唐僧方向飞去！\n"NOR,users());
	        	message("system",HIW"【"+HIR+"西天取经"+HIW+"】"+HIY+"玉鼠"+NOR"："+who->name()+"做的好，莫要管那猴子，快些进洞来！\n"NOR,users());
	        	message("system",HIW"【"+HIR+"西天取经"+HIW+"】"+HIY+who->name()+NOR"：是，夫人！"+who->name()+"使了个土遁，进了无底洞！\n"NOR,users());
	        	who->move("/d/qujing/wudidong/inner-tang");
        	}
        	if( who->query_temp("daojian/swk") == "begin" )
        	{
	        	who->set_temp("daojian/swk","done");
	        	message("system",HIW"【"+HIR+"西天取经"+HIW+"】"+HIY+"悟空"+NOR"：妖怪好生厉害，还是找人帮忙吧。孙悟空架起筋斗云找人帮忙去了！\n"NOR,users());
	        	message("system",HIW"【"+HIR+"西天取经"+HIW+"】"+HIY+"玉鼠"+NOR"："+who->name()+"做的好，莫要管那猴子，快些进洞来！\n"NOR,users());
	        	message("system",HIW"【"+HIR+"西天取经"+HIW+"】"+HIY+who->name()+NOR"：是，夫人！"+who->name()+"使了个土遁，进了无底洞！\n"NOR,users());
	        	who->move("/d/qujing/wudidong/inner-tang");
        	}
        	if( who->query_temp("daojian/lijing") == "begin" )
        	{
        		message("system",HIW"【"+HIR+"西天取经"+HIW+"】"+HIY+"悟空"+NOR"：妖怪太厉害了，我先躲一下！\n"NOR,users());
        	}
        }
        load_object("/obj/empty");
        me->move("/obj/empty");
        call_out ("destruct_me",3,me);
}
int accept_fight(object ob)
{	
        object me=this_object();
	if( ob != query("owner") )
	{
		message_vision(CYN"$N说道：快走开，别打扰你孙爷爷。\n"NOR,me);
	 	return 0;
	}
}
int accept_kill(object ob)
{	
        object me=this_object();
	if( ob != query("owner") )
	{
		message_vision(CYN"$N说道：快走开，别打扰你孙爷爷。\n"NOR,me);
	 	return 0;
	}
}
void destruct_me (object me)
{
  destruct (me);
}

void unconcious()
{
   die();
}
void heart_beat()
{
        if (!query_temp("weapon") && !query_temp("added"))
        {
	        set_temp("added", 1);
	        set("force_factor",100);
	        set("force",5000);
        }
        if (query("eff_kee")<query("max_kee"))
        {
	        command("eat yao");
		command("exert recover");
	}
	else
	{
	 	command("surrender");
		command("exert recover");
	}
        ::heart_beat();
}
