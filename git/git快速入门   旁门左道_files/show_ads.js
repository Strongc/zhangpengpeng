
(function(){var g=true,h=null,i=false,j=(new Date).getTime();var k=this,aa=function(a,b,c){a=a.split(".");c=c||k;!(a[0]in c)&&c.execScript&&c.execScript("var "+a[0]);for(var d;a.length&&(d=a.shift());)if(!a.length&&b!==undefined)c[d]=b;else c=c[d]?c[d]:c[d]={}},ba=function(a){return a.call.apply(a.bind,arguments)},ca=function(a,b){var c=b||k;if(arguments.length>2){var d=Array.prototype.slice.call(arguments,2);return function(){var f=Array.prototype.slice.call(arguments);Array.prototype.unshift.apply(f,d);return a.apply(c,f)}}else return function(){return a.apply(c,
arguments)}},l=function(){l=Function.prototype.bind&&Function.prototype.bind.toString().indexOf("native code")!=-1?ba:ca;return l.apply(h,arguments)};var da=/&/g,ea=/</g,fa=/>/g,ga=/\"/g,m={"\u0000":"\\0","\u0008":"\\b","\u000c":"\\f","\n":"\\n","\r":"\\r","\t":"\\t","\u000b":"\\x0B",'"':'\\"',"\\":"\\\\"},p={"'":"\\'"},t=function(a,b){if(a<b)return-1;else if(a>b)return 1;return 0};var u,v,w,z,B=function(){return k.navigator?k.navigator.userAgent:h};z=w=v=u=i;var C;if(C=B()){var ha=k.navigator;u=C.indexOf("Opera")==0;v=!u&&C.indexOf("MSIE")!=-1;w=!u&&C.indexOf("WebKit")!=-1;z=!u&&!w&&ha.product=="Gecko"}var D=v,F=z,ja=w,G;
a:{var H="",I;if(u&&k.opera){var J=k.opera.version;H=typeof J=="function"?J():J}else{if(F)I=/rv\:([^\);]+)(\)|;)/;else if(D)I=/MSIE\s+([^\);]+)(\)|;)/;else if(ja)I=/WebKit\/(\S+)/;if(I){var ka=I.exec(B());H=ka?ka[1]:""}}if(D){var K,la=k.document;K=la?la.documentMode:undefined;if(K>parseFloat(H)){G=String(K);break a}}G=H}
var ma=G,na={},L=function(a){var b;if(!(b=na[a])){b=0;for(var c=String(ma).replace(/^[\s\xa0]+|[\s\xa0]+$/g,"").split("."),d=String(a).replace(/^[\s\xa0]+|[\s\xa0]+$/g,"").split("."),f=Math.max(c.length,d.length),e=0;b==0&&e<f;e++){var ta=c[e]||"",s=d[e]||"",n=RegExp("(\\d*)(\\D*)","g"),A=RegExp("(\\d*)(\\D*)","g");do{var q=n.exec(ta)||["","",""],o=A.exec(s)||["","",""];if(q[0].length==0&&o[0].length==0)break;b=t(q[1].length==0?0:parseInt(q[1],10),o[1].length==0?0:parseInt(o[1],10))||t(q[2].length==
0,o[2].length==0)||t(q[2],o[2])}while(b==0)}b=na[a]=b>=0}return b};var M,N;N=M=i;var O=B();if(O)if(O.indexOf("Firefox")!=-1)M=g;else if(O.indexOf("Camino")==-1)if(!(O.indexOf("iPhone")!=-1||O.indexOf("iPod")!=-1))if(O.indexOf("iPad")==-1)if(O.indexOf("Android")==-1)if(O.indexOf("Chrome")!=-1)N=g;var oa=M,pa=N;var qa=document,P=window;var Q=function(a){a=parseFloat(a);return isNaN(a)||a>1||a<0?0:a},ra=function(a){if(a=="true")return g;return i},sa=/^([\w-]+\.)*([\w-]{2,})(\:[0-9]+)?$/,ua=function(a){if(!a)return"pagead2.googlesyndication.com";return(a=a.match(sa))?a[0]:"pagead2.googlesyndication.com"};var va=Q("0"),wa=Q("0"),xa=Q("0.25"),ya=Q("0.2");var za=ra("false"),Aa=ra("false"),Ba=ra("false");var Ca=function(){return ua("")};!D||L("9");!F&&!D||D&&L("9")||F&&L("1.9.1");D&&L("9");ua("");var R=function(a){return!!a&&typeof a=="function"&&!!a.call},Da=function(a){if(!(arguments.length<2))for(var b=1,c=arguments.length;b<c;++b)a.push(arguments[b])};function S(a){return typeof encodeURIComponent=="function"?encodeURIComponent(a):escape(a)}function Ea(a,b){if(a.attachEvent)a.attachEvent("onload",b);else a.addEventListener&&a.addEventListener("load",b,i)}
function Fa(a,b){if(!(Math.random()<1.0E-4)){var c=Math.random();if(c<b)return a[Math.floor(c/b*a.length)]}return""};aa("google_protectAndRun",function(a,b,c){a=l(b,k,a);b=window.onerror;window.onerror=a;try{c()}catch(d){c=d.toString();var f="";if(d.fileName)f=d.fileName;var e=-1;if(d.lineNumber)e=d.lineNumber;if(!a(c,f,e))throw d;}window.onerror=b},void 0);
aa("google_handleError",function(a,b,c,d){if(Math.random()<0.01){a=["http://",Ca(),"/pagead/gen_204","?id=jserror","&jscb=",za?1:0,"&jscd=",Aa?1:0,"&context=",S(a),"&msg=",S(b),"&file=",S(c),"&line=",S(d.toString()),"&url=",S(qa.URL.substring(0,512)),"&ref=",S(qa.referrer.substring(0,512))];a.push(["&client=",S(P.google_ad_client),"&format=",S(P.google_ad_format),"&slotname=",S(P.google_ad_slot),"&output=",S(P.google_ad_output),"&ad_type=",S(P.google_ad_type)].join(""));a=a.join("");P.google_image_requests||
(P.google_image_requests=[]);b=new Image;b.src=a;P.google_image_requests.push(b)}return!Ba},void 0);var Ha=function(a){try{var b=a.google_test;a.google_test=!b;if(a.google_test===!b){a.google_test=b;return g}}catch(c){}return i},Ia=h,Ja=function(){if(!Ia){for(var a=window;a!=a.parent&&Ha(a.parent);)a=a.parent;Ia=a}return Ia};var T,U=function(a){this.d=[];this.b=a||window;this.a=0;this.c=h},Ka=function(a,b){this.j=a;this.o=b};U.prototype.i=function(a,b){if(this.a==0&&this.d.length==0&&(!b||b==window)){this.a=2;this.h(new Ka(a,window))}else this.f(a,b)};U.prototype.f=function(a,b){this.d.push(new Ka(a,b||this.b));La(this)};U.prototype.k=function(a){this.a=1;if(a)this.c=this.b.setTimeout(l(this.g,this),a)};U.prototype.g=function(){if(this.a==1){if(this.c!=h){this.b.clearTimeout(this.c);this.c=h}this.a=0}La(this)};
U.prototype.m=function(){return g};U.prototype.nq=U.prototype.i;U.prototype.nqa=U.prototype.f;U.prototype.al=U.prototype.k;U.prototype.rl=U.prototype.g;U.prototype.sz=U.prototype.m;var La=function(a){a.b.setTimeout(l(a.n,a),0)};U.prototype.n=function(){if(this.a==0&&this.d.length){var a=this.d.shift();this.a=2;a.o.setTimeout(l(this.h,this,a),0);La(this)}};U.prototype.h=function(a){this.a=0;a.j()};
var Ma=function(a){try{return a.sz()}catch(b){return i}},Na=function(a){return!!a&&(typeof a=="object"||typeof a=="function")&&Ma(a)&&R(a.nq)&&R(a.nqa)&&R(a.al)&&R(a.rl)},Oa=function(){if(T&&Ma(T))return T;var a=Ja(),b=a.google_jobrunner;if(Na(b))return T=b;return a.google_jobrunner=T=new U(a)},Pa=function(a,b){Oa().nq(a,b)},Qa=function(a,b){Oa().nqa(a,b)};var Ra=function(a,b,c){var d=["<iframe"],f;for(f in a)a.hasOwnProperty(f)&&Da(d,f+"="+a[f]);d.push('style="left:0;position:absolute;top:0;"');d.push("></iframe>");b="border:none;height:"+c+"px;margin:0;padding:0;position:relative;visibility:visible;width:"+b+"px";return['<ins style="display:inline-table;',b,'"><ins id="',a.id+"_anchor",'" style="display:block;',b,'">',d.join(" "),"</ins></ins>"].join("")};var Sa=function(){},Ua=function(a,b,c){switch(typeof b){case "string":Ta(a,b,c);break;case "number":c.push(isFinite(b)&&!isNaN(b)?b:"null");break;case "boolean":c.push(b);break;case "undefined":c.push("null");break;case "object":if(b==h){c.push("null");break}if(b instanceof Array){var d=b.length;c.push("[");for(var f="",e=0;e<d;e++){c.push(f);Ua(a,b[e],c);f=","}c.push("]");break}c.push("{");d="";for(f in b)if(b.hasOwnProperty(f)){e=b[f];if(typeof e!="function"){c.push(d);Ta(a,f,c);c.push(":");Ua(a,
e,c);d=","}}c.push("}");break;case "function":break;default:throw Error("Unknown type: "+typeof b);}},Va={'"':'\\"',"\\":"\\\\","/":"\\/","\u0008":"\\b","\u000c":"\\f","\n":"\\n","\r":"\\r","\t":"\\t","\u000b":"\\u000b"},Wa=/\uffff/.test("\uffff")?/[\\\"\x00-\x1f\x7f-\uffff]/g:/[\\\"\x00-\x1f\x7f-\xff]/g,Ta=function(a,b,c){c.push('"');c.push(b.replace(Wa,function(d){if(d in Va)return Va[d];var f=d.charCodeAt(0),e="\\u";if(f<16)e+="000";else if(f<256)e+="00";else if(f<4096)e+="0";return Va[d]=e+f.toString(16)}));
c.push('"')};var V=["google_ad_block","google_ad_channel","google_ad_client","google_ad_format","google_ad_height","google_ad_host","google_ad_host_channel","google_ad_host_tier_id","google_ad_output","google_ad_override","google_ad_region","google_ad_section","google_ad_slot","google_ad_type","google_ad_width","google_adtest","google_allow_expandable_ads","google_alternate_ad_url","google_alternate_color","google_analytics_domain_name","google_analytics_uacct","google_bid","google_city","google_color_bg","google_color_border",
"google_color_line","google_color_link","google_color_text","google_color_url","google_container_id","google_contents","google_country","google_cpm","google_ctr_threshold","google_cust_age","google_cust_ch","google_cust_gender","google_cust_id","google_cust_interests","google_cust_job","google_cust_l","google_cust_lh","google_cust_u_url","google_disable_video_autoplay","google_ed","google_eids","google_enable_osd","google_encoding","google_font_face","google_font_size","google_frame_id","google_gl",
"google_hints","google_image_size","google_kw","google_kw_type","google_language","google_max_num_ads","google_max_radlink_len","google_num_radlinks","google_num_radlinks_per_unit","google_num_slots_to_rotate","google_only_ads_with_video","google_only_pyv_ads","google_only_userchoice_ads","google_override_format","google_page_url","google_referrer_url","google_region","google_reuse_colors","google_rl_dest_url","google_rl_filtering","google_rl_mode","google_rt","google_safe","google_skip","google_tag_info",
"google_targeting","google_ui_features","google_ui_version","google_video_doc_id","google_video_product_type","google_with_pyv_ads"];var Xa=function(a){this.b=a;a.google_iframe_oncopy||(a.google_iframe_oncopy={handlers:{},log:[],img:Math.random()<0.01?[]:h});this.e=a.google_iframe_oncopy;a.setTimeout(l(this.l,this),3E4)},Ya;var W="var i=this.id,s=window.google_iframe_oncopy,H=s&&s.handlers,h=H&&H[i],w=this.contentWindow,d;try{d=w.document}catch(e){}if(h&&d&&(!d.body||!d.body.firstChild)){if(h.call){i+='.call';setTimeout(h,0)}else if(h.match){i+='.nav';w.location.replace(h)}s.log&&s.log.push(i)}";
if(/[&<>\"]/.test(W)){if(W.indexOf("&")!=-1)W=W.replace(da,"&amp;");if(W.indexOf("<")!=-1)W=W.replace(ea,"&lt;");if(W.indexOf(">")!=-1)W=W.replace(fa,"&gt;");if(W.indexOf('"')!=-1)W=W.replace(ga,"&quot;")}Ya=W;Xa.prototype.set=function(a,b){this.e.handlers[a]=b};
Xa.prototype.l=function(){if(this.e.img){var a=this.e.log,b=this.b.document;if(a.length){b=["http://",Ca(),"/pagead/gen_204?id=iframecopy&log=",S(a.join("-")),"&url=",S(b.URL.substring(0,512)),"&ref=",S(b.referrer.substring(0,512))].join("");a.length=0;a=new Image;this.e.img.push(a);a.src=b}}};var Za=function(){var a="script";return["<",a,' src="http://',ua(""),'/pagead/js/r20101117/r20110307/show_ads_impl.js"></',a,">"].join("")},$a=function(a,b,c,d){return function(){var f=i;d&&Oa().al(3E4);try{var e;try{e=!!a.document.getElementById(b).contentWindow.document}catch(ta){e=i}if(e){var s=a.document.getElementById(b).contentWindow,
n=s.document;if(!(n.body&&n.body.firstChild)){n.open();s.google_async_iframe_close=g;n.write(c)}}else{var A=a.document.getElementById(b).contentWindow,q;e=c;e=String(e);if(e.quote)q=e.quote();else{s=['"'];for(n=0;n<e.length;n++){var o=e.charAt(n),Ga=o.charCodeAt(0),ob=s,pb=n+1,ia;if(!(ia=m[o])){var E;if(Ga>31&&Ga<127)E=o;else{var r=o;if(r in p)E=p[r];else if(r in m)E=p[r]=m[r];else{var x=r,y=r.charCodeAt(0);if(y>31&&y<127)x=r;else{if(y<256){x="\\x";if(y<16||y>256)x+="0"}else{x="\\u";if(y<4096)x+=
"0"}x+=y.toString(16).toUpperCase()}E=p[r]=x}}ia=E}ob[pb]=ia}s.push('"');q=s.join("")}A.location.replace("javascript:"+q)}f=g}catch(vb){A=Ja().google_jobrunner;Na(A)&&A.rl()}f&&(new Xa(a)).set(b,$a(a,b,c,i))}},ab=function(){return va&&wa/va||typeof window.google_hash_ratio=="number"&&window.google_hash_ratio||h};window.google_loader_used=g;(function(a){if(!("google_onload_fired"in a)){a.google_onload_fired=i;Ea(a,function(){a.google_onload_fired=g})}})(window);if(!window.google_loader_experiment)window.google_loader_experiment=Fa(["async1_all","block1"],ya)||Fa(["launch"],xa)||"none";var bb,cb=window.google_loader_experiment;
if(bb=window.google_enable_async===g||cb=="launch"||cb=="async1_all")bb=window.google_enable_async===i?i:(D&&/MSIE 8/.test(navigator.userAgent)||pa||oa&&!!window.document.body)&&!window.google_container_id&&(!window.google_ad_output||window.google_ad_output=="html");
if(bb){var db=window;if(db.google_unique_id)++db.google_unique_id;else db.google_unique_id=1;for(var X=window,_script$$inline_211="script",Y,Z={allowtransparency:'"true"',frameborder:'"0"',height:'"'+X.google_ad_height+'"',hspace:'"0"',marginwidth:'"0"',marginheight:'"0"',onload:'"'+Ya+'"',scrolling:'"no"',vspace:'"0"',width:'"'+X.google_ad_width+'"'},eb=X.document,$=Z.id,fb=0;!$||X.document.getElementById($);)$="aswift_"+fb++;Z.id=$;Z.name=$;eb.write(Ra(Z,X.google_ad_width,X.google_ad_height));Y=
$;var gb;if(X.google_page_url)X.google_page_url=String(X.google_page_url);for(var hb=[],ib=0,jb=V.length;ib<jb;ib++){var kb=V[ib];if(X[kb]!=h){var lb;try{var mb=[];Ua(new Sa,X[kb],mb);lb=mb.join("")}catch(nb){}lb&&Da(hb,kb,"=",lb,";")}}gb=hb.join("");for(var qb=0,rb=V.length;qb<rb;qb++)X[V[qb]]=h;var sb=(new Date).getTime(),tb=ab(),ub=window.google_loader_experiment,wb=["<!doctype html><html><body><",_script$$inline_211,">",gb,"google_show_ads_impl=true;google_unique_id=",X.google_unique_id,';google_async_iframe_id="',
Y,'";google_start_time=',j,";",tb?"google_hash_ratio="+tb+";":"",ub?'google_loader_experiment="'+ub+'";':"","google_bpp=",sb>j?sb-j:1,";</",_script$$inline_211,">",Za(),"</body></html>"].join("");(X.document.getElementById(Y)?Pa:Qa)($a(X,Y,wb,g))}else{window.google_start_time=j;window.google_hash_ratio=ab();document.write(Za())};})();
