 //sgzl
#include <ansi.h>

inherit NPC;

void create()
{
  set_name(HIW"猪八戒"NOR,({"zhu bajie","zhu","bajie"}));
  set("gender", "男性");
  set("title", HIY"二徒弟"NOR);
  set("age", 35);
  set("attitude", "heroism");
  set("class", "xian");
  set("combat_exp", 2000000);
  set("daoxing", 2000000);
  set("kee", 2600);
  set("max_kee", 2600);
  set("sen", 2800);
  set("max_sen", 2800);
  set("force", 7000);
  set("max_force", 3500);
  set("mana", 7000);
  set("max_mana", 3500);
  set("force_factor", 40);
  set("mana_factor", 40);
  set("str", 40);
  set("per", 10);

  set_skill("unarmed", 200+random(50));
  set_skill("dodge", 200+random(50));
  set_skill("parry", 200+random(50));
  set_skill("rake", 200+random(50));
  set_skill("force", 200+random(50));
  set_skill("spells", 200+random(50));
  set_skill("baguazhou", 200+random(50));
  set_skill("yanxing-steps", 200+random(50));
  set_skill("skyriver-rake", 200+random(50));
  map_skill("force", "lengquan-force");
  map_skill("spells", "baguazhou");
  map_skill("rake", "skyriver-rake");
  map_skill("parry", "skyriver-rake");
  map_skill("dodge", "yanxing-steps");
  
  set_temp("apply/attack", 200);
  set_temp("apply/defense", 200);
  set_temp("apply/armor", 200);
  set_temp("apply/damage", 200);  
  set("force_factor",300);
  set("mana_factor",300);
  set("bellicosity",300);
  set("nk_gain", 100+random(50));
  set("nk_factor", 12);
  
   setup();
        carry_object("/d/kaifeng/obj/jiuchipa")->wield();
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
   	message("system",HIW"【"+HIR+"西天取经"+HIW+"】"+HIY+"八戒"+NOR"：师傅没有妖怪，我们上路吧！师徒四人匆匆向西天赶去！\n"NOR,users());
   	if( who )
   		who->set_temp("daojian/zbj","fail");
   	remove_call_out("leave");
        destruct(this_object());
}

void die ()
{
        object me = this_object();
        object who = me->query("owner");
        if( query_temp("last_damage_from") == who )
        {
        	who->set_temp("daojian/zbj","done");	
        	message("system",HIW"【"+HIR+"西天取经"+HIW+"】"+HIY+"玉鼠"+NOR"："+who->name()+"做的好，快把猪八戒抓进洞来！\n"NOR,users());
        	message("system",HIW"【"+HIR+"西天取经"+HIW+"】"+HIY+who->name()+NOR"：是，夫人！"+who->name()+"抓起猪八戒，使了个土遁，进了无底洞！\n"NOR,users());
        	message("system",HIW"【"+HIR+"西天取经"+HIW+"】"+HIY+"玉鼠"+NOR"：小的们，把猪八戒看好了！猪八戒被众小妖抬着进了内洞。\n"NOR,users());
        	who->move("/d/qujing/wudidong/inner-tang");
        }
        else
        {
        	message("system",HIW"【"+HIR+"西天取经"+HIW+"】"+HIY+"八戒"+NOR"：师傅，妖怪好厉害！猪八戒架狂风找人帮忙去了！\n"NOR,users());
        	if( who )
   			who->set_temp("daojian/zbj","fail");
        }
        load_object("/obj/empty");
        me->move("/obj/empty");
        call_out ("destruct_me",3,me);
  
}

void destruct_me (object me)
{
  	destruct(me);
}

int accept_fight(object ob)
{	
        object me=this_object();
	if( ob != query("owner") )
	{
		message_vision(CYN"$N说道：快走开，别打扰你猪爷爷。\n"NOR,me);
	 	return 0;
	}
}
int accept_kill(object ob)
{	
        object me=this_object();
	if( ob != query("owner") )
	{
		message_vision(CYN"$N说道：快走开，别打扰你猪爷爷。\n"NOR,me);
	 	return 0;
	}
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
	        set("force",2000);
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