// guanyin.c 观音菩萨
// By 九天(take) 


inherit NPC;
inherit F_MASTER;
#include <ansi.h>
int begin_go();
int do_drop(object, object);

string ask_mieyao();
string ask_cancel();

void create()
{
	set_name("观音菩萨", ({ "guanyin pusa", "guanyin", "pusa" }));
	set("title", "救苦救难大慈大悲");
	set("long", @LONG
理圆四德，智满金身。眉如小月，眼似双星。兰心欣紫竹，
蕙性爱得藤。她就是落伽山上慈悲主，潮音洞里活观音。
LONG);
	set("gender", "女性");
	set("age", 35);
	set("attitude", "peaceful");
	set("rank_info/self", "贫僧");
	set("rank_info/respect", "菩萨娘娘");
	set("class", "bonze");
        	set("str",24);
	set("per",100);//means no rong-mao description.
	set("max_kee", 5000);
	set("max_gin", 5000);
	set("max_sen", 5000);
	set("force", 4000);
	set("max_force", 2000);
	set("force_factor", 145);
	set("max_mana", 3000);
	set("mana", 6000);
	set("mana_factor", 150);
	set("combat_exp", 2000000);
	set("daoxing", 10000000);

	set_skill("literate", 150);
	set_skill("spells", 200);
	set_skill("buddhism", 200);
	set_skill("unarmed", 150);
	set_skill("jienan-zhi", 150);
	set_skill("dodge", 180);
	set_skill("lotusmove", 180);
	set_skill("parry", 180);
	set_skill("force", 180);
	set_skill("lotusforce", 180);
	set_skill("staff", 180);
	set_skill("lunhui-zhang", 180);
	map_skill("spells", "buddhism");
	map_skill("unarmed", "jienan-zhi");
	map_skill("dodge", "lotusmove");
	map_skill("force", "lotusforce");
	map_skill("parry", "lunhui-zhang");
	map_skill("staff", "lunhui-zhang");
	set("chat_chance_combat", 80);
	set("chat_msg_combat", ({
		//(: cast_spell, "bighammer" :),
		(: perform_action, "staff", "chaodu" :),
		(: perform_action, "staff", "pudu" :),
	}) );
	set("inquiry",([
      "灵台观礼"    : (: begin_go :),
      "cancel": (: ask_cancel :),
      "降妖": (: ask_mieyao :),
      "净瓶": "前些天，福星借我的净瓶用，到现在也没有还，你去看看吧。" ]));

	//let's use cast bighammer to protect her...weiqi:)
	create_family("南海普陀山", 1, "菩萨");

	setup();
	carry_object("/d/nanhai/obj/jiasha")->wear();
	carry_object("/d/nanhai/obj/nine-ring")->wield();
}

string ask_mieyao()
{
    object who=this_player();
        
    if((string)who->query("family/family_name")=="南海普陀山") {
      command("say 灭妖除魔，乃我佛门中人之本分。");
      return "/d/obj/mieyao"->query_yao(who);
    }
    return ("非我门人,何故来此?\n");
}

string ask_cancel()
{
	object me=this_player();
	if((int)me->query_temp("m_mieyao"))
	{
	      me->add("daoxing",-2000);
	      me->delete_temp("m_mieyao");
	      me->delete("secmieyao");
	      me->delete("secmieyao/type");
	      me->delete("secmieyao/location");
	      me->delete("secmieyao/place");
	      me->delete("secmieyao/name");
	      me->delete("secmieyao/id");
	     return ("没用的东西！");
	}
	else
	{
	     return ("你有任务吗？！");
	}
}

void attempt_apprentice(object ob)
{
	if (!((string)ob->query("bonze/class") =="bonze" )) {
		command("say 我佛门神通广大，" + RANK_D->query_respect(ob) + "欲成正果，先入我门。\n");
		write("看样子观音菩萨对你未剃度出家颇为不快。\n");
		return;
	}	
	if (((int)ob->query_skill("buddhism", 1) < 100 )) {
		command("say " + RANK_D->query_respect(ob) + "不在佛法上苦修，恐怕难成正果。\n");
		return;
	}
	command("pat " + ob->query("id") );
	command("say 好！这才是我佛门的好弟子。只要多加努力，定可早成正果。\n");

	command("recruit " + ob->query("id") );
	return;	
}
void die()
{
	int i;
	string file;
	object *inv;
	object who = query_temp("last_damage_from");
	object hong;
	if( objectp(who) && who->query_temp("huohun/zhenshen") )
	{
		who->delete_temp("huohun/zhenshen");
		hong = present("honghai er",environment());
		if( hong && random(who->query("int")) > 20 - random( who->query("lunhui_zhuanshi") ) )
		{
			who->add("huohun_known",1);
   			message("chat",HIC+"\n\n〖"+HIW+"惊天谣传"+HIC+"〗红孩儿(honghai er)：" + who->name() + "助我夺回真身，终于领悟到了"+HIR"[火魂]"+HIC"！\n\n\n"NOR,users());
		}
		else
		{
			who->set("huohun_cant",1);
   			message("chat",HIC+"\n\n〖"+HIW+"惊天谣传"+HIC+"〗红孩儿(honghai er)：" + who->name() + "虽然成功助我夺回真身，却无缘学习"+HIR"[火魂]"+HIC"真是可惜！\n\n\n"NOR,users());
		}
		if( hong )
		{
			message_vision(HIR"\n\n红孩儿眼见时机已到，化作一团红雾向枯松涧火云洞飞去。\n"NOR,who);
			destruct(hong);
		}
		
	}
        if( environment() ) {
        message("sound", "\n\n观音菩萨摇头叹道：刚离迷障，又入魔障，世间疾苦，何人度之！\n\n", environment());
        command("sigh");
        message("sound", "\n观音菩萨驾祥云，登彩雾，径往西方去了。。。\n\n", environment());
        inv = all_inventory(this_object());
	for(i=0; i<sizeof(inv); i++) {
		if (inv[i]->query("no_drop")) continue;
		do_drop(this_object(), inv[i]);
//		if (stringp(file = find_command("drop")) && 
//			call_other(file, "do_drop", this_object(), inv[i])) ;
	}
	}

	destruct(this_object());
}

int do_drop(object me, object obj) {
  if (obj->move(environment(me))) {
      //d_mana>0 is for "bian". mon 11/05/97
      if((obj->query_temp("d_mana"))>0) {
            if( obj->query_temp("is_living")==1 )
                 message_vision("$N将$n从背上放了下来，躺在地上。\n", me, obj);
            else {
                 message_vision( sprintf("$N丢下一%s$n。\n",
                 undefinedp(obj->query_temp("unit"))?
	                 "个":obj->query_temp("unit")
                         ), me, obj );
           }
      } else {
           if( obj->is_character() )
                  message_vision("$N将$n从背上放了下来，躺在地上。\n", me, obj);
           else {
             message_vision( sprintf("$N丢下一%s$n。\n", obj->query("unit")),
                     me, obj );
             if( !obj->query("value") && !obj->value() ) {
                tell_object(me,"因为这样东西并不值钱，所以人们并不会注意到它的存在
		   。\n");
                destruct(obj);
             }
           }
      }
      return 1;
  }
  return 0;
}


void unconcious()
{
	die();
}

int accept_object(object me,object ob)
{       
	    string myname=RANK_D->query_respect(me), thing=(string)ob->query("id");
		object who;
        who=this_object();
      
	if (me->query("fangcun/panlong_putuo")=="begin")
	{
	  if (ob->query("name") == "〖刀法入门〗")
      {
      command ("nod");
      command ("say 这是长安城里三联书局的刀法入门！");
      me->set_temp("putuo/basic_blade","done");
      call_out("destroy", 1, ob);
      return 1;
	  }
	  if (ob->query("name") == "〖拳法入门〗")
      {
      command ("nod");
      command ("say 这是长安城里三联书局的拳法入门！");
      me->set_temp("putuo/basic_unarmed","done");
      call_out("destroy", 1, ob);
      return 1;
	  }
	  if (ob->query("name") == "〖道德经〗")
      {
      command ("smile");
      command ("say 这是车迟国三清观内藏经楼的道德经还是灵台方寸山的经阁中的收藏呢？");
     me->set_temp("putuo/daode","done");
      call_out("destroy", 1, ob);
      return 1;
	  }
	  if (ob->query("name") == "〖伏魔山心经〗")
      {
      command ("ah");
      command ("say 这本〖伏魔山心经〗蕴含着求书者不少的心血,得来这本书着实不易！");
     me->set_temp("putuo/forcebook","done");
      call_out("destroy", 1, ob);
      return 1;
	  }
	  if (ob->query("name") == "〖女儿经〗")
      {
      command ("nod");
      command ("say 这本〖女儿经〗在月宫练功房乃为其女弟子读书识字之用！");
     me->set_temp("putuo/girlbook","done");
      call_out("destroy", 1, ob);
      return 1;
	  }
      if (ob->query("name") == "〖青莲剑谱〗")
      {
      command ("nod");
      command ("say 这是诗仙之物,只怕是用桂花酒换来的！");
     me->set_temp("putuo/jianpu","done");
      call_out("destroy", 1, ob);
      return 1;
	  }
	  if (ob->query("name") == "〖金刚经〗")
      {
      command ("bow");
      command ("say 此乃我佛如来之大成佛法,一直留在南海普陀书院中！");
     me->set_temp("putuo/jingang","done");
      call_out("destroy", 1, ob);
      return 1;
	  }
	  if (ob->query("name") == "〖旧书〗")
      {
      command ("nod");
      command ("say 这是长安城东,望南街内的武学书籍,上面记载了刀，斧，叉，锤，锏，钯，枪，杖，棒，剑十种基本武功！");
     me->set_temp("putuo/misc","done");
      call_out("destroy", 1, ob);
      return 1;
	  }
	  if (ob->query("name") == "〖无字天书〗")
      {
      command ("nod");
      command ("say 此乃袁守诚处得来的法术要领！");
     me->set_temp("putuo/nowords","done");
      call_out("destroy", 1, ob);
      return 1;
	  }
	  if (ob->query("name") == "〖格斗秘诀〗")
      {
      command ("nod");
      command ("say "+RANK_D->query_respect(me)+ "帮助高员外除去强盗,品行可嘉！");
     me->set_temp("putuo/parry_book","done");
      call_out("destroy", 1, ob);
      return 1;
	  }
	  if (ob->query("name") == "〖千字文〗")
      {
      command ("nod");
      command ("say 是灵台方寸山广羲子道长手里的〖千字文〗吗？");
     me->set_temp("putuo/qian","done");
      call_out("destroy", 1, ob);
      return 1;
	  }
	  if (ob->query("name") == "〖拳经〗")
      {
      command ("nod");
      command ("say 这是长安武馆范青平所藏格斗技巧．");
     me->set_temp("putuo/quanjing","done");
      call_out("destroy", 1, ob);
      return 1;
	  }
      if (ob->query("name") == "〖三字经〗")
      {
      command ("nod");
      command ("say 这〖三字经〗一书我南海普陀书院,长安书社以及月宫练功房都收有此书,当真是流传甚广．");
     me->set_temp("putuo/san","done");
      call_out("destroy", 1, ob);
      return 1;
	  }
	   if (ob->query("name") == "〖枪法简介〗")
      {
      command ("nod");
      command ("say 这是大唐将军府内的藏书,记载了枪法的运用．");
     me->set_temp("putuo/spearbook","done");
      call_out("destroy", 1, ob);
      return 1;
	  }
	   if (ob->query("name") == "〖杖法简要〗")
      {
      command ("nod");
      command ("say 此乃我南海普陀书院之物．");
     me->set_temp("putuo/staffbook","done");
      call_out("destroy", 1, ob);
      return 1;
	  }
	  if (ob->query("name") == "碎布头")
      {
      command ("hmm");
      command ("say 这碎布头沾满杀气,"+RANK_D->query_respect(me)+ "为何因一身外之物大开杀戒？");
     me->set_temp("putuo/stickbook","done");
      call_out("destroy", 1, ob);
      return 1;
	  }
	  if (ob->query("name") == "〖风水〗")
      {
      command ("nod");
      command ("say 这是东海熬来国老妇人的家传书籍．");
     me->set_temp("putuo/windwater","done");
      call_out("destroy", 1, ob);
      return 1;
	  }
	  else
      {
      command ("say 这是什么？");
      call_out("dropthing", 1, thing);
      return 1;
      }
     }
  else
  command ("shake ");
  return 0;
}
void destroy(object ob)
{
        destruct(ob);
        return;
}

void dropthing(string thing)
{
  command("drop "+thing);
  return;
}

int begin_go()
{
	object me,ob;
    int dx,dx1,wx,qn;
	me=this_player();
	ob=this_object();
	dx=(me->query("daoxing"))/20;
if (dx>=100000) dx=100000;
	dx1=dx/1000;
	wx=(me->query("combat_exp"))/20;
if (wx>=10000) wx=10000;
	qn=30000;
    
		if (!me->query("fangcun/panlong_visite"))
	return 0;
		if (me->query("guanli/putuo"))
	return 0;

		if (me->query("fangcun/panlong_putuo")=="done")
	{
        message_vision(HIW"\n观音道：既然"+RANK_D->query_respect(me)+ "来请,我们这就动身吧！\n"NOR,me);
        message_vision(HIY"\n观音菩萨已然驾祥云往西北方向三星洞飞去！\n"NOR,me);
		ob->move("/d/lingtai/inside1");
        return 1;
	}
   		
		if ((me->query_temp("putuo/basic_blade")=="done") 
			&& (me->query_temp("putuo/basic_unarmed")=="done")
			&& (me->query_temp("putuo/daode")=="done")
			&& (me->query_temp("putuo/forcebook")=="done")
			&& (me->query_temp("putuo/girlbook")=="done")
			&& (me->query_temp("putuo/jianpu")=="done")
			&& (me->query_temp("putuo/jingang")=="done")
			&& (me->query_temp("putuo/misc")=="done")
			&& (me->query_temp("putuo/nowords")=="done")
			&& (me->query_temp("putuo/parry_book")=="done")
			&& (me->query_temp("putuo/qian")=="done")
			&& (me->query_temp("putuo/quanjing")=="done")
			&& (me->query_temp("putuo/san")=="done")
			&& (me->query_temp("putuo/spearbook")=="done")
			&& (me->query_temp("putuo/staffbook")=="done")
			&& (me->query_temp("putuo/stickbook")=="done")
			&& (me->query_temp("putuo/windwater")=="done"))
	{
		me->add("fangcun/panlong_visite",1);
		me->set("fangcun/panlong_putuo","done");
       message("chat",HIC+"〖"+HIW+"大唐西游"+HIC+"〗观音菩萨(Guanyin pusa)："+me->query("name")+"助我收齐武学精要,届时贫僧一定上灵台观礼！\n"NOR,users());
             message("chat",HIC+"〖"+HIW+"大唐西游"+HIC+"〗观音菩萨(Guanyin pusa)："+me->query("name")+"得到奖励：道行"+chinese_number(dx1)+"年，武学"+wx+"点，潜能30000点．\n"NOR,users());
		if (me->query("family/family_name")=="方寸山三星洞")
           message_vision("\n观音菩萨道：观礼之日还请" + RANK_D->query_respect(me) + "再来告知一声.\n"NOR,me);
		me->add("daoxing",dx);
		me->add("combat_exp",wx);
		me->add("potential",30000);
	    if ((me->query("family/family_name")!="方寸山三星洞")||(me->query("fangcun/panlong_noway")))
			me->set("guanli/putuo",1);
		return 1;
	}				
		if ((me->query("fangcun/panlong_putuo")!="begin")&&(me->query("fangcun/panlong_visite")))
    {
  command("say "+me->query("name")+"来的不凑巧,我正为收集东土大唐所有基本武学书籍忙碌,要去灵台观礼只怕没有空闲！\n");
  command("sigh ");
   me->set("fangcun/panlong_putuo","begin");
	return 1;
	}

  message_vision("\n观音菩萨自言自语的说道：据说顺风耳消息灵通,问他关于武学书籍的事情,他应该略有所知.\n"NOR,me);
  return 1;
}

�
