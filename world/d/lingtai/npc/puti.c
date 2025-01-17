//puti.c
inherit NPC;
inherit F_MASTER;
#include <ansi.h>
int cure_longear();
int begin_go();
int bian_yuan();
int fly_sea();
int ask_longjin();
int ask_pansi();

void create()
{
       set_name(HIW"菩提祖师"NOR, ({"master puti","puti", "master"}));
       set("long", "大觉金仙没垢姿，西方妙相祖菩提\n");
       set("title", HIC"斜月三星"NOR);
       set("gender", "男性");
       set("age", 100);
	set("class", "taoist");
       set("attitude", "friendly");
       set("shen_type", 1);
       set("rank_info/respect", "老师祖");
       set("per", 26);
	set("looking", "玉面多光润，苍髯颌下飘，金睛飞火焰，长目过眉梢。");
	set("int", 30);
       set("max_kee", 5000);
       set("max_gin", 1000);
       set("max_sen", 5000);
       set("force", 5000);
       set("max_force", 2500);
       set("force_factor", 150);
       set("max_mana", 2500);
       set("mana", 5000);
       set("mana_factor", 150);
       set("combat_exp", 3000000);
	set("daoxing", 10000000);

       set_skill("literate", 180);
       set_skill("unarmed", 180);
       set_skill("dodge", 180);
       set_skill("parry", 180);
	set_skill("stick", 200);
	set_skill("sword", 180);
	set_skill("liangyi-sword", 180);
	set_skill("spells", 200);
	set_skill("dao", 180);
	set_skill("puti-zhi", 180);
	set_skill("wuxiangforce", 200);
	set_skill("force", 200);
	set_skill("qianjun-bang", 180);
	set_skill("jindouyun", 180);
	map_skill("spells", "dao");
	map_skill("unarmed", "puti-zhi");
	map_skill("force", "wuxiangforce");
	map_skill("stick", "qianjun-bang");
	map_skill("parry", "qianjun-bang");
	map_skill("dodge", "jindouyun");
	map_skill("sword", "liangyi-sword");
	set("chat_chance_combat", 60);
        set("chat_msg_combat", ({
		(: cast_spell, "light" :),
		(: cast_spell, "dingshen" :),
                (: cast_spell, "thunder" :)
        }) );
    set("inquiry",([
    "灵台观礼": (: begin_go :),
    "八仙": (: fly_sea :),
    "紫霞": (: ask_pansi :),
    "青霞": (: ask_pansi :),
    "紫霞仙子": (: ask_pansi :),
    "青霞仙子": (: ask_pansi :),
    "龙筋": (: ask_longjin :),
	"顺风耳": (: cure_longear :),  
	"算命先生": (: bian_yuan :),  
	"袁守诚": (: bian_yuan :),  
]));
create_family("方寸山三星洞", 1, "蓝");
setup();

        carry_object("/d/lingtai/obj/pao")->wear();
        carry_object("/d/lingtai/obj/shoe")->wear();
        carry_object("/d/lingtai/obj/putibang")->wield();
}

void init()
{
        object me;
    me=this_player();

        ::init();
        
	   if (me->query("fangcun/panlong_accept")=="done")
		   return;
       if (me->query("fangcun/panlong_nowaylingtai"))
		   return;

	   if (me->query("fangcun/panlong_accept")=="begin")
	{
		call_out("panlong_accept",2,me);
		return;
	}
	   
	   
	   if ((me->query("fangcun/panlong_qiansi_finish")==1)&&(!me->query("fangcun/panlong_noway")))
		{
                
			if ((me->query("fangcun/panlong_visite")>=1) && (me->query("fangcun/panlong_visite")<11))
			{
				call_out("begin_visite2",2);
			    return;
			}
			
			if (me->query("fangcun/panlong_visite")>=11)
	      {
            command("say 徒儿，你的数据出问题了，最好找九天（ｔａｋｅ）了解一下情况\n");
			me->move("/d/wiz/outjail");
            me->save();
			 return;
		  }
				remove_call_out("greeting");
                call_out("greeting", 2, me);
        
	     return;
		 }
    
		

}

int accept_object(object me, object ob)
{
  if ((me->query("fangcun/panlong_wzg_rsg")=="done")||(me->query("fangcun/panlong_wzg")=="done"))
	{	 
	 if (ob->query("id") == "renshen guo")
	{
	 command ("nod "+me->query("id"));
      command ("say 呵呵，徒儿真是辛苦了！");
      me->delete("fangcun/panlong_nowaywzg2");
      call_out("destroy", 1, ob);
      return 1;
	}
	}
return 0;
}

int begin_go()
{
	object me,ob;
    int visite;
	me=this_player();
	ob=this_object();
  
   if (me->query("fangcun/panlong_accept")=="done")
	{
        command("say " + RANK_D->query_respect(me) + "，你已经领悟了盘龙八式，还来干什么！\n");
		return 0;
	}

   if (me->query("family/family_name")!="方寸山三星洞")
      return 0;
   
  
   if (me->query("fangcun/panlong_nowaylingtai"))
	{
        command("say " + RANK_D->query_respect(me) + "，你已经邀请过一次了，这个锻炼机会还是让给别人吧！\n");
		return 0;
	}

	if (me->query("betray/count"))
   {
     me->delete("fangcun");
     command("say 徒儿，你判师后来投我方寸山，这盘龙八式你是学不会的．\n");
	 return 0;
   }

   if (!me->query("fangcun/panlong_visite"))
	return 0;
//   sscanf(me->query("fangcun/panlong_visite"),"%d",visite);
   

		if (me->query("fangcun/panlong_visite")<=3)
	       {
	        command("say 徒儿，你所邀请到的门派似乎太少！\n");
            return 1;
		   }     	
	    	
       visite=me->query("fangcun/panlong_visite");
       me->set_temp("panlong_visite",visite);
		   		
		if (me->query("fangcun/panlong_nowayshushan"))
			me->add_temp("panlong_visite",-1);
     	if (me->query("fangcun/panlong_nowayputuo"))
			me->add_temp("panlong_visite",-1);
     	if (me->query("fangcun/panlong_nowaymoon"))
			me->add_temp("panlong_visite",-1);
     	if (me->query("fangcun/panlong_nowaylonggong"))
			me->add_temp("panlong_visite",-1);
     	if (me->query("fangcun/panlong_nowayjjf"))
			me->add_temp("panlong_visite",-1);
     	if (me->query("fangcun/panlong_nowaywzg1"))
			me->add_temp("panlong_visite",-1);
        if (me->query("fangcun/panlong_nowaywzg2"))
			me->add_temp("panlong_visite",-1);
		if (me->query("fangcun/panlong_nowaywzg3"))
			me->add_temp("panlong_visite",-1);
        if (me->query("fangcun/panlong_nowaypansi"))
			me->add_temp("panlong_visite",-1);
		if (me->query("fangcun/panlong_nowayhell"))
			me->add_temp("panlong_visite",-1);
	   if (!me->query("fangcun/panlong_times"))
            me->set("fangcun/panlong_times",1);
	       else
	       {
	         me->add("fangcun/panlong_times",1);
		   }
       if (me->query_temp("panlong_visite")<=4)
	       {
     		  //me->delete("fangcun");
			  command("say 逆徒，你还有脸回来！\n");
	       	  me->set("fangcun/panlong_nowaylingtai",1);

            return 0;
		   }     	
		      
		
		   call_out("finish_visite",1,me);
return 1;
}

void attempt_apprentice(object ob)
{	ob=this_player();
	if( (string)ob->query("family/family_name")=="方寸山三星洞") {
	if ((int)ob->query("daoxing") < 500000 ) {
  	command("say 我们修真之士最重的就是道行，" + RANK_D->query_respect(ob) + "还需多加努力才能早悟大道。\n");
	return;
	}
/*
	if( (int)ob->query("pending/kick_out")) {
	command("say 这位" + RANK_D->query_respect(ob) + "反复无常，老夫不原再收你为徒了！\n");
	command("sigh");
	return;
	}
*/
	if ((int)ob->query_int() < 35) {
	command("say 这位" + RANK_D->query_respect(ob) + "悟性太低，恐怕收了你也难有作为！\n");
	command("sigh");
	return;
	}
	if( (int)ob->query_skill("dao", 1) < 120 ) {
	command("say 这位" + RANK_D->query_respect(ob) + "对我道家仙法领会还不够深，现在收你也是勉为其难，不如作罢！\n");
	command("sigh");
	return;
	}
        command("smile");
        command("say 很好，" + RANK_D->query_respect(ob) + "多加努力，他日必定有成。");
        command("recruit " + ob->query("id") );
	return;
	}
        command("shake");
        command("say 老夫不收外门弟子，" + RANK_D->query_respect(ob) + "还是另寻他人吧！\n");
        return;
}
int recruit_apprentice(object ob)
{
        if( ::recruit_apprentice(ob) )
                ob->set("class", "taoist");
}

int accept_fight(object me, object ob)
{	ob=this_player();
	command("say " + RANK_D->query_rude(ob) + "杀心太重，恐祸不久已！\n");
	return 0;
}
void die()
{

        if( environment() ) {
        message("sound", "\n\n菩提祖师微皱眉头，道：这厮果是个天成地就的！\n\n", environment());
        command("sigh");
        message("sound", "\n菩提祖师身形一转，化做青烟走了。。。\n\n", environment());
        }

        destruct(this_object());
}

int fly_sea()
{
      object me;
    me=this_player();
	  if (me->query("fangcun/panlong_wzg")!="begin")
		  return 0;
	message_vision("\n菩提祖师掐指一算，笑道：那镇元老道哪里是不知八仙所愿？八仙虽得道多载，其贪玩本性难改，
	                五庄观主训徒极严，只好假装不知，想借我徒儿之手圆他徒孙们一个
		        心愿．傻徒儿，你去问问八仙"+HIY"重游东海"+NOR"之事，便可知道他们所想了．\n\n",me);
	me->set_temp("wzg_baxian","go");
	return 1;
}

int ask_longjin()
{
      object me;
    me=this_player();
    if ((me->query("fangcun/panlong_hell_18")=="done")&&(me->query("fangcun/panlong_hell_longjin")=="begin"))
	{
			message_vision("\n菩提祖师略点了点头道：徒儿，这龙筋刚柔兼顾，坚韧并存，乃是制鞭子的上好材料，只不过每条龙身
	              上也才一条主筋可以锻造那阎罗地府的神兵--缚龙索。"+NOR"何况，龙若失其筋，焉
	              能存活？欲得龙筋必先灭其身。徒儿，你可紧记"+HIY"若杀恶龙，则为民除害，若错
                      杀善龙，则是滥杀无辜，为我仙家所不耻．\n\n"NOR,me);
	        return 1;
	}
    return 0;
}

int ask_pansi()
{
	object me;
    me=this_player();
	if (me->query("fangcun/panlong_nowaypansi"))
	{
			message_vision("\n菩提祖师仰天长叹一声道：那青霞和紫霞原是如来佛祖日月明灯上缠绕在一起的两根灯芯。因姐妹俩不合，
			私逃下界后一直相互争斗，事到如今也是天意如此，唉。。。。。。\n\n",me);
    		command ("sigh " + me->query("id"));
			return 1;
	}
	if (me->query("fangcun/panlong_pansi")=="done")
	{
			message_vision("\n菩提祖师微笑着点头道：那青霞和紫霞原是如来佛祖日月明灯上缠绕在一起的两根灯芯。因姐妹俩不合，
                      私逃下界后一直相互争斗。徒儿，你最终化解她姐妹二人千年怨恨，使其二人
                      得以皈依我佛，实乃功德无量。至于为此得罪天将也不必太放在心上，凡大事
                      不拘小节，如此才合为师的性子。\n\n",me);
    		command ("haha ");
			return 1;
	}
	return 0;
}

int cure_longear()
{
      object me;
    me=this_player();
	  if (!me->query_temp("putuo/longear"))
		  return 0;

		command ("haha " + me->query("id"));
		call_out("cure_longear1",3);
		return 1;
}

void cure_longear1()
{
   	object me;
    me=this_player();

	message_vision("\n菩提祖师哈哈大笑道：傻徒儿，定是那顺风耳老毛病又犯了，这有何难？"+HIY"狗尾草"+NOR+""+"清热消疳与"+HIY"牛黄
	            "+NOR""+"之祛风解毒最宜用于左耳疼痛．"+HIY"紫荆"+NOR""+"活血消肿辅以"+HIY"陈皮"+NOR""+"顺气化痰之功效治
                    右耳疾可药到病除．\n",me);
}

int bian_yuan()
{
	object me;
    me=this_player();
	  if (me->query_temp("fangcun/panlong_longgong_yuanshoucheng")!="begin")
		  return 0;
    command ("hmm " + me->query("id"));
	call_out("bian_yuan1",3);
    return 1;
}

void bian_yuan1()
{
   	object me;
    me=this_player();
	message_vision("\n菩提祖师略有所思道：徒儿，凡事都事出有因，东海龙王说算命先生设计陷害泾河龙王
                    乃至玉帝降旨斩之，你可去问过那算命先生"+HIY"泾河龙王"+NOR"之事，听他
	            如何说法？除邪扶正，替天行道乃我道家宗旨，但切不可妄做推
	            断，误伤好人．\n\n",me);
}

void greeting(object ob)
{
        command ("nod " + ob->query("id"));
		if( !ob || !visible(ob) || environment(ob) != environment() ) return;
                message_vision("\n\n"NOR,ob);
				command ("say " + "乖徒儿,自你师兄孙悟空悟出千均棒法绝学[盘龙八式]以后千年来,我灵台
              方寸山无一弟子能步其后尘,今日得见我"+ob->query("name")+"徒儿悟性如此之佳,当真是我
              方寸山的福分！我这般年纪能得你这徒儿,老朽也心满意足已．\n\n" );
	call_out("begin_visite", 1, ob);
}

void begin_visite(object me)
{
command("say " + me->query("name") + ",你听好了[盘龙八式]乃我方寸山千均棒法中的终极绝招,是以小无相
              功作为根基,道家仙法为辅助,与敌人战斗中运真气于棒法中,一口气连出
              八招,招招凶猛.如你日后能有此造化学成[盘龙八式]也不要忘记降妖除魔
              ,替天行道,拯救天下苍生的做人之道！\n\n");
     call_out("begin_visite1", 1, me);
}

void begin_visite1(object me)
{
	 
      command("say 现在你就上路去邀请各位仙家的掌门前来我“灵台观礼”,届时我当众传
	      授你[盘龙八式],至于能否领略其中奥妙就全看你的缘分了,去吧,去吧！\n");
      me->set("fangcun/panlong_visite",1);
}

void begin_visite2()
{
	command("say 乖徒儿，可遇到什么难处？");
}

void finish_visite(object ob)
{
   command("smile");
   command("say 乖徒儿,事情都办完了,马上到正院来.");
   message_vision(HIW"\n菩提祖师说完就不见了！\n"NOR,ob);
   this_object()->move("/d/lingtai/inside1");
  // ob->delete("fangcun/panlong_visite");
   ob->set("fangcun/panlong_accept","begin");
   ob->delete("fangcun/panlong_qiansi");
}

void panlong_accept(object me)
{
 int pass;
 me->delete_temp("panlong_nopass");
 me->delete_temp("master");
 me->delete_temp("take_panlong");
 if ((present("bai mei"))&&(!userp(present("bai mei"))))
    {
	 me->add_temp("take_panlong",1);
	 me->set_temp("master/shushan","come");
	}
if ((present("xi wangmu"))&&(!userp(present("xi wangmu"))))
    {
	 me->add_temp("take_panlong",1);
	 me->set_temp("master/moon","come");
	}
if ((present("lao ren"))&&(!userp(present("lao ren"))))
    {
	 me->add_temp("take_panlong",1);
	 me->set_temp("master/jjf","come");
	}
if ((present("guanyin pusa"))&&(!userp(present("guanyin pusa"))))
    {
	 me->add_temp("take_panlong",1);
	 me->set_temp("master/putuo","come");
	}
if ((present("ao guang"))&&(!userp(present("ao guang"))))
    {
	 me->add_temp("take_panlong",1);
	 me->set_temp("master/longgong","come");
	}
if ((present("zhenyuan daxian"))&&(!userp(present("zhenyuan daxian"))))
    {
	 me->add_temp("take_panlong",1);
	 me->set_temp("master/wzg","come");
	}
if ((present("dizang pusa"))&&(!userp(present("dizang pusa"))))
    {
	 me->add_temp("take_panlong",1);
	 me->set_temp("master/hell","come");
	}
if (!me->query("fangcun/panlong_nowaywzg3"))
	 me->add_temp("take_panlong",1);
if (!me->query("fangcun/panlong_nowaywzg2"))
	 me->add_temp("take_panlong",1);
if (!me->query("fangcun/panlong_nowaywzg1"))
	 me->add_temp("take_panlong",1);
if (!me->query("fangcun/panlong_nowayshushan"))
	 me->add_temp("take_panlong",1);
if (!me->query("fangcun/panlong_nowaylonggong"))
	 me->add_temp("take_panlong",1);
if (!me->query("fangcun/panlong_nowaypansi"))
	 me->add_temp("take_panlong",1);
if (!me->query("fangcun/panlong_nowayhell"))
	 me->add_temp("take_panlong",1);
if (!me->query("fangcun/panlong_nowayputuo"))
	 me->add_temp("take_panlong",1);
if (!me->query("fangcun/panlong_nowaymoon"))
	 me->add_temp("take_panlong",1);


pass=random(me->query_temp("take_panlong")) + random( me->query("lunhui_zhuanshi") );
if (pass<=10)
	me->set_temp("panlong_nopass",1);
me->set_temp("pass/total",me->query_temp("take_panlong"));                          // waring del
me->set_temp("pass/random",pass);                          // waring del
 message("chat",HIC+"〖"+HIW+"大唐西游"+HIC+"〗菩提祖师(Master puti)：我徒儿"+me->query("name")+"悟出盘龙精要，今日邀请各位仙家道友同来灵台观礼！\n\n"NOR,users());
message_vision(HIC"\n众人都向菩提祖师抱拳见礼．\n\n"NOR,me);

message_vision(HIC"\n菩提祖师转过身来对$N道：乖徒儿，盘龙八式旨在悟，而不是学．你注意看好了．\n"NOR,me);
call_out("direct_panlong",5,me);
}

void direct_panlong(object me)
{
	message_vision(HIY"\n菩提祖师一摆手中菩提杖，陡然间一股劲气从菩提祖师的道袍中汹涌冲出．\n"NOR,me);
    message_vision(HIY"\n\n菩提祖师顿时化作一团金光，舞起千均棒法，身形灵动，暗蕴杀机，猛然间一声清啸，震耳欲聋．\n"NOR,me);
	message_vision(HIY"\n\n啸声初起，菩提祖师竟使菩提杖电光石火般的连攻八招，那金光好似“盘龙出沧海，踏云啸九天”．
	气势之所及，刹时正院中落叶尽去，石凳石桌被盘龙劲气震碎成无数小块，$N内力不及，
        竟也被盘龙劲气所伤．\n"NOR,me);
    me->set("eff_kee",(me->query("eff_kee"))/20);
	me->set("kee",(me->query("kee"))/10);
	me->set("eff_sen",(me->query("eff_sen"))/20);
	me->set("sen",(me->query("sen"))/10);
    message_vision(HIY"\n菩提祖师收住招式，众仙家均赞叹叫好．\n"NOR,me);
	message_vision(HIR"\n\n$N受了重伤，支持不住，一下子坐倒在地．\n"NOR,me);
	message_vision(HIC"\n菩提祖师走到$N面前和声道：徒儿，你好好体会一下．看看能悟出点什么来．\n"NOR,me);
	call_out("direct_panlong1",10,me);
}

void direct_panlong1(object me)
{
	   message_vision(HIC"\n\n\n菩提祖师拱手抱拳对各派掌门道：今日盘龙观礼到此为止，各位远道而来还请到贫道山中一游，也让贫道一尽地主之宜．\n"NOR,me);
   if (me->query_temp("master/shushan"))
	{
            message_vision(HIC"\n白眉(Bai mei)：好个盘龙，气势之霸道，天下绝招无一能及．\n"NOR,me);
        destruct(present("bai mei"));
	}
   if (me->query_temp("master/moon"))
	   {
          message_vision(HIC"\n西王母(Xi wangmu)：多年不见，菩提大师依然威风不减当年，叫人好生佩服．\n"NOR,me);
          message_vision(HIC"菩提祖师(Master puti)：王母娘娘过奖了．\n"NOR,me);
		  destruct(present("xi wangmu"));
		}
   if (me->query_temp("master/jjf"))
	{   
       message_vision(HIC"\n白发老人(Lao ren)：今日能再见菩提大师的盘龙八式，真是不枉此行呀．\n"NOR,me);
	   destruct(present("lao ren"));
	}
   if (me->query_temp("master/putuo"))
	{
	   message_vision(HIC"\n观音菩萨(Guanyin pusa)：难怪那猴子一条如意金箍棒大闹天宫之时，一招盘龙众天将无人能挡．\n"NOR,me);
	   destruct(present("guanyin pusa"));
	}
   if (me->query_temp("master/longgong"))
	{
	   message_vision(HIC"\n熬广(Ao guang)：那定海神针铁．．．．．．唉．．．．．．幸亏就这么一只猴子．\n"NOR,me);
	   destruct(present("ao guang"));
	}
   if (me->query_temp("master/wzg"))
	{
	   message_vision(HIC"\n镇元大仙(zhenyuan daxian)：哈哈哈哈，我那结拜兄弟本事可不小呀．\n"NOR,me);
	   destruct(present("zhenyuan daxian"));
	}
	if (me->query_temp("master/hell"))
	{
	   message_vision(HIC"\n地藏王菩萨(Dizang pusa)：灵台弟子真是英雄辈出，代代有能人．\n"NOR,me);
	   destruct(present("dizang pusa"));
	}
       message("chat",HIC+"\n\n〖"+HIY+"大唐西游"+HIC+"〗菩提祖师哈哈大笑了几声。\n"NOR,users());
	message_vision(HIC"\n菩提祖师(Master puti)：各位道友，我们暂且不提这猴头，老道这就头前领路带大家看看我方寸山的景致如何？\n"NOR,me);
	message_vision(HIY"\n众人一同欣然抱拳道：请．\n"NOR,me);
   message_vision("\n\n$N盘腿在地等候师傅示下．突然耳边轻轻传来菩提祖师的声音：\n"NOR,me);
   message_vision(HIR"\n徒儿，我带众人离开，我送你到小室静心潜思，能否掌握"+HIY"盘龙八式 "+HIR"就在此一举．\n"NOR,me);
   message_vision(HIB"\n$N盘腿闭目静静的回想刚才师傅所使的"+HIY"盘龙八式"+NOR"．\n",me);
   me->start_busy(20);
   me->move("/d/lingtai/lou");
	call_out("direct_panlong2",15,me);
}

void direct_panlong2(object me)
{
   if (!me->query_temp("panlong_nopass"))
	{
	   message_vision(HIR"\n\n\n    $N潜思半日，突觉脑中灵气四起，宛如自己置身于一片空地手持"+HIY"金箍棒"+HIR"，不停歇的使出盘
龙八式，直到浑身汗如雨下，半晌$N睁开眼睛，心里如海啸来临前般的平静，终于掌握了"+HIY"盘龙"+HIR"绝技！\n"NOR,me);
message("chat",HIC+"\n\n〖"+HIW+"惊天谣传"+HIC+"〗某人："+ me->name()+"通过灵台观礼考验，终于掌握了"+HIY"盘龙"+HIR"绝技！\n"NOR,users());
	  // me->delete("fangcun");
	   me->set("fangcun/panlong_accept","done");
	   me->set("fangcun/panlong_qiansi_finish",1);
       present("master puti")->move("/d/lingtai/room");
	   return;
	}
   message_vision(HIR"\n\n\n$N潜思半日，头脑中一片混乱，只依稀记住师傅所使的的招式，终不能化为己用．\n"NOR,me);
   message("chat",HIC+"\n\n〖"+HIW+"惊天谣传"+HIC+"〗某人："+ me->name()+"虽然通过灵台观礼考验，可惜缘分未到，终不能掌握了"+HIY"盘龙"+HIR"绝技！\n"NOR,users());
   present("master puti")->move("/d/lingtai/room");
   me->delete("fangcun/panlong_accept");
   if (me->query("fangcun/panlong_times"))
   {
	   //me->delete("fangcun");
	   me->set("fangcun/panlong_qiansi_finish",1);
       me->set("fangcun/panlong_nowaylingtai",1);
   }
}

void destroy(object ob)
{
  destruct(ob);
}

�
