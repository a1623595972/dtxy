// zhangguolao.c...weiqi, 98.02.24.
#include <ansi.h>
int fly_sea();
void qi_maolu();
inherit NPC;
void create()
{
	set_name("张果老", ({"zhang guolao", "zhang", "guolao"}));
	//set("title", "");
	set("gender", "男性" );
	set("age", 50);
	set("per", 20);
	set("long", "一位笑嘻嘻的滑稽老头。\n");
	set("class", "xian");
	set("combat_exp", 120000);
  set("daoxing", 500000);

	set("attitude", "peaceful");
	create_family("五庄观", 3, "弟子");
	set_skill("unarmed", 60);
	set_skill("wuxing-quan", 60);
	set_skill("dodge", 80);
	set_skill("baguazhen", 70);
	set_skill("parry", 80);
	set_skill("hammer", 90);
	set_skill("kaishan-chui", 100);
	set_skill("force", 70);   
	set_skill("zhenyuan-force", 70);
	set_skill("literate", 50);
	set_skill("spells", 80);
	set_skill("taiyi", 80);
	map_skill("spells", "taiyi");
	map_skill("force", "zhenyuan-force");
	map_skill("unarmed", "wuxing-quan");
	map_skill("hammer", "kaishan-chui");
	map_skill("dodge", "baguazhen");

	set("max_kee", 500);
	set("max_sen", 500);
	set("force", 1000);
	set("max_force", 800);
	set("mana", 1600);
	set("max_mana", 800);	
	set("force_factor", 40);
	set("mana_factor", 40);

	set("maolu", 0);

	setup();
	carry_object("/d/obj/cloth/linen")->wear();
	carry_object("/d/obj/cloth/pobuxie")->wear();
	carry_object("/d/obj/weapon/hammer/jiuhulu")->wield();
}

void init()
{       
	object ob=this_player();
	object me=this_object();

	::init();

	set("chat_chance", 10);
	set("inquiry", ([
	    "重游东海": (: fly_sea :),
		"name" : "呵呵！张果老是也。\n",
		"here" : "今儿个醉了，还真被你问倒了。\n",
	 ]) );

	set("chat_msg", ({
		"张果老嘻嘻嘻地笑了几声。\n",	
		"张果老拿起酒葫芦又灌了一口，满意地咂了咂嘴。\n",
		"张果老打了个响指：哈哈，我的小毛驴就是听话。\n",
		(: random_move :)
	}) );

	if( query("maolu") == 0 )
	{
                  //call_out("qi_maolu", 1);
                    //qi_maolu();
		set("maolu", 1);
	}

}

int fly_sea()
{
  string *jnames = ({
    "热酒",
    "清白老酒",
    "水酒",
    "酥合香油",
    "淡茶",
    "江米酒",
    "老白干",
	"米酒",
	"羊奶酒",
	"泡的已经没有味的茶水",
	"清水",
	"白烧酒",
	"桂花酒",
	"云雾山香茶",
	"碧樨茶",
	"玄火酒",
	"西湖龙井茶",
	"清茶",
	});  
   	string jname;
	object me,ob;
    me=this_player();
	ob=this_object();

	  if( me->query_temp("wzg_baxian")!="go" )
		  return 0;
      if (me->query("wzggive/zhangguolao"))
    	{
	 		  message_vision(WHT"\n张果老问道：那"+CYN""+me->query("wzggive/zhangguolao")+WHT"可曾带来了吗？！\n"NOR,me);
			  return 1;
		}
	  if( me->query_temp("wzg/zhangguolao")!="give")
	    {
	      jname = jnames[random(sizeof(jnames))];
		  message_vision(WHT"\n张果老摸了摸胡子说道：我们八仙一直都想再游一次东海，今日" + RANK_D->query_respect(me) + "说起，不如我们一
		      同去，只是老头子我最近特别想喝点"+CYN""+jname+WHT"．\n"NOR,me);
		  me->set("wzggive/zhangguolao",jname);
		  return 1;
		}
	command("say " + RANK_D->query_respect(me) + "快去叫上其他八仙，我先走一步了！\n");
	ob->move("/d/changan/eastseashore");
    return 1;
}

int accept_object(object who, object ob)
{
	  object me = this_object();

	  if( !who->query("wzggive/zhangguolao"))
		  return 0;
	  if ((string)ob->query("liquid/name")!=who->query("wzggive/zhangguolao"))
   {
     command ("shake "+who->query("id"));
	call_out ("return_ob",1,who,ob);
    return 1;
  }
  

  message_vision(WHT"\n$N接过$n尝了尝，不由得皱了皱眉头道：人都说"+who->query("wzggive/zhangguolao")+"味道独特，怎么还不如我的米酒香醇．\n"NOR,me,ob);
  who->set_temp("wzg/zhangguolao","give");
  who->delete("wzggive/zhangguolao");
  return 1;
}



void return_ob (object who, object ob)
{
  if (ob)
    command ("give "+ob->query("id")+" to "+who->query("id"));
}

void qi_maolu()
{
	object maolu;

	if (!present("xiao maolu")) {
        	maolu = new(__DIR__"xiaomaolu.c");
        	maolu->move( environment(this_object()) );
        }
	command("mount maolu");
	return;	
}

void attempt_apprentice(object ob)
{
	if( (string)ob->query("family/family_name")=="五庄观" )
	{
		if( (int)ob->query("family/generation") < 3  )
		{
			if ( (string)ob->query("gender") == "男性" ) command("say 师叔见笑了。\n");
			else command("say 师姑见笑了。\n");
		}
		else if( (int)ob->query("family/generation") ==3  )
		{
			if ( (string)ob->query("gender") == "男性" ) command("say 师兄太客气了。\n");
			else command("say 师妹太客气了。\n");
		}
		else 
		{
			command("consider");
			command("say 是你自己要拜的，你师父打上门来我可得拿你挡。\n");
			command("recruit " + ob->query("id") );
		}
	}

	else
	{
		command("say 好，好好干，张果老不行，徒弟可不能差了。\n");
		command("recruit " + ob->query("id") );
	}

	return;
}

int recruit_apprentice(object ob)
{
	if( ::recruit_apprentice(ob) )
		ob->set("class", "xian");
}




�
