//petitioning the electoral college...
//runs from moshetrenk.com/email on submit

<?php
	$me = $_POST['email'];
	$emails = array("bash@paulashmgt.com","sharongiese08@yahoo.com","paddywagon@cox.net","agutier@azgohs.gov","jane518@cox.net","governordaugaard@state.sd.us","ashley.mcmillan@cloudcorp.net","mark.kahrs@house.ks.gov","mark@kahrsforkansas.com","ron@treasurer.ks.gov","clay.l.barker@gmail.com","kellyarnold@yahoo.com","irelandwinslow@att.net","info@maldonadoortho.com","ccrawford@wallacesaunders.com","tom.brown@mail.house.gov","gyclerk@centurytel.net","keithg@pinncom.com","swright028@yahoo.com","info@trahanlaw.com","lharsch@nobts.edu","c21gil@yahoo.com","louisavallone@mac.com","kaykelloggkatz@usa.net","vern.breland@yahoo.com","lennierhys@cox.net","glendapollard@cox.net","info@montinotary.com","jbatt@cityofno.com","raymondgriffinjr@yahoo.com","sbeckley@indiana.gop","lauracampbellforcouncil@gmail.com","jcardwell@indiana.gop","jcardwell@jeffcardwell.com","donald.hayes@twc.com","rlkpatrick55@gmail.com","ethan_manning@yahoo.com","manningauctions@gmail.com","esimcox@indianaenergy.org","chuck@clwilliamscompanies.com","ronpfoster@yahoo.com","info@patrickmorrisey.com","ann@annurling.com","urlingfortreasurer@gmail.com","macwarner@warnerforsos.com","will.hickman@sbcglobal.net","landonestay@gmail.com","shellie.surles@gmail.com","sactx@sbcglobal.net","sandscholar@gmail.com","tinagibsonsd17srec@gmail.com","muenzler@texas.net","texas24elector@outlook.com","marian.knowlton@gmail.com","rteter@dpisd.org","jewett@williamsoncountygop.org","wgreene@southtexascollege.edu","info@seanparnellak.com","carolynleman@gmail.com","arwcyes@yahoo.com","kimtrvs@gmail.com","kimbabler@hotmail.com","brianwestrate@gmail.com","bradcourtney1@yahoo.com","katzkiernan@att.net","bethscottclayton@comcast.net","jason.mumpower@cot.tn.gov","c.holiway@att.net","lynnedavisrealtor@gmail.com","cedesigners@frontiernet.net","gopdrewster@att.net","azevedo@negia.net","bburdette@doe.k12.ga.us","lhdill@surfsouth.com","randy.evans@dentons.com","bobbie@bdfrantz.com","rblittle.gop@gmail.com","mccord0304@gmail.com","kshook@oconeeschools.org","dcd123navyman@yahoo.com","medsingleton@gmail.com","tmsheldon1776@gmail.com","bbozzuto@pagop.org","bbozzuto@northallegheny.org","tchristian@dmgs.com","mdowning@pagop.org","mferraro@northamptoncounty.org","robgleasongop@gmail.com","joycehaas1@yahoo.com","khare@penn.com","jmcerlane@lambmcerlane.com","tpickett@pahousegop.com","pickett528@gmail.com","areilly@swartzcampbell.com","csides3@comcast.net","rws@jdsw.com","lawrence.tabas@obermayer.com","christinejtoretti@mac.com","sheriffbunny@comcast.net","dylan@iowagop.org","rcarlisle@nd.gov","larry@larryahern.com","julietbarnett@yahoo.com","jbrown0185@comcast.net","denasurvey@gmail.com","joegruters@gmail.com","blaise.ingoglia@myfloridahouse.gov","miraclevisor@msn.com","joenegron@joenegron.com","carlos@votetrujillo.com","nwatkins@robertwatkins.com","samhunt59@yahoo.com","judyrapanos@aol.com","wdseelig@gmail.com","kecrider@gmail.com","biker50jim@yahoo.com","hankfuhs@juno.com","jguzman@msu.edu");
    
	$subject = "My petition as a voter and a citizen";
	$txt = "Hello, \nI\'m writing to you to request that you cast your vote on the good side of history and serve in favor of the people. In the interest of the future of our country and humanity and in favor of the greater good, please place your vote against Donald Trump. Mr. Trump has demonstrated open malice and indicated his ineptitude as a politician. He is clearly not equipped for the presidency and I beg you not to put him there. \nSincerely,\nA concerned voter.";
    	$headers = "From: ".$me."\r\n";
	foreach($emails as $email){	
		mail($email,$subject,$txt,$headers);
	}

	echo "Sent from ".$me;

?>