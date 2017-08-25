<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE eagle SYSTEM "eagle.dtd">
<eagle version="7.2.0">
<drawing>
<settings>
<setting alwaysvectorfont="no"/>
<setting verticaltext="up"/>
</settings>
<grid distance="0.01" unitdist="inch" unit="inch" style="lines" multiple="1" display="yes" altdistance="0.01" altunitdist="inch" altunit="inch"/>
<layers>
<layer number="1" name="Top" color="4" fill="1" visible="no" active="no"/>
<layer number="16" name="Bottom" color="1" fill="1" visible="no" active="no"/>
<layer number="17" name="Pads" color="2" fill="1" visible="no" active="no"/>
<layer number="18" name="Vias" color="2" fill="1" visible="no" active="no"/>
<layer number="19" name="Unrouted" color="6" fill="1" visible="no" active="no"/>
<layer number="20" name="Dimension" color="15" fill="1" visible="no" active="no"/>
<layer number="21" name="tPlace" color="7" fill="1" visible="no" active="no"/>
<layer number="22" name="bPlace" color="7" fill="1" visible="no" active="no"/>
<layer number="23" name="tOrigins" color="15" fill="1" visible="no" active="no"/>
<layer number="24" name="bOrigins" color="15" fill="1" visible="no" active="no"/>
<layer number="25" name="tNames" color="7" fill="1" visible="no" active="no"/>
<layer number="26" name="bNames" color="7" fill="1" visible="no" active="no"/>
<layer number="27" name="tValues" color="7" fill="1" visible="no" active="no"/>
<layer number="28" name="bValues" color="7" fill="1" visible="no" active="no"/>
<layer number="29" name="tStop" color="7" fill="3" visible="no" active="no"/>
<layer number="30" name="bStop" color="7" fill="6" visible="no" active="no"/>
<layer number="31" name="tCream" color="7" fill="4" visible="no" active="no"/>
<layer number="32" name="bCream" color="7" fill="5" visible="no" active="no"/>
<layer number="33" name="tFinish" color="6" fill="3" visible="no" active="no"/>
<layer number="34" name="bFinish" color="6" fill="6" visible="no" active="no"/>
<layer number="35" name="tGlue" color="7" fill="4" visible="no" active="no"/>
<layer number="36" name="bGlue" color="7" fill="5" visible="no" active="no"/>
<layer number="37" name="tTest" color="7" fill="1" visible="no" active="no"/>
<layer number="38" name="bTest" color="7" fill="1" visible="no" active="no"/>
<layer number="39" name="tKeepout" color="4" fill="11" visible="no" active="no"/>
<layer number="40" name="bKeepout" color="1" fill="11" visible="no" active="no"/>
<layer number="41" name="tRestrict" color="4" fill="10" visible="no" active="no"/>
<layer number="42" name="bRestrict" color="1" fill="10" visible="no" active="no"/>
<layer number="43" name="vRestrict" color="2" fill="10" visible="no" active="no"/>
<layer number="44" name="Drills" color="7" fill="1" visible="no" active="no"/>
<layer number="45" name="Holes" color="7" fill="1" visible="no" active="no"/>
<layer number="46" name="Milling" color="3" fill="1" visible="no" active="no"/>
<layer number="47" name="Measures" color="7" fill="1" visible="no" active="no"/>
<layer number="48" name="Document" color="7" fill="1" visible="no" active="no"/>
<layer number="49" name="Reference" color="7" fill="1" visible="no" active="no"/>
<layer number="51" name="tDocu" color="7" fill="1" visible="no" active="no"/>
<layer number="52" name="bDocu" color="7" fill="1" visible="no" active="no"/>
<layer number="90" name="Modules" color="5" fill="1" visible="yes" active="yes"/>
<layer number="91" name="Nets" color="2" fill="1" visible="yes" active="yes"/>
<layer number="92" name="Busses" color="1" fill="1" visible="yes" active="yes"/>
<layer number="93" name="Pins" color="2" fill="1" visible="no" active="yes"/>
<layer number="94" name="Symbols" color="4" fill="1" visible="yes" active="yes"/>
<layer number="95" name="Names" color="7" fill="1" visible="yes" active="yes"/>
<layer number="96" name="Values" color="7" fill="1" visible="yes" active="yes"/>
<layer number="97" name="Info" color="7" fill="1" visible="yes" active="yes"/>
<layer number="98" name="Guide" color="6" fill="1" visible="yes" active="yes"/>
</layers>
<schematic xreflabel="%F%N/%S.%C%R" xrefpart="/%S.%C%R">
<libraries>
<library name="frames">
<description>&lt;b&gt;Frames for Sheet and Layout&lt;/b&gt;</description>
<packages>
</packages>
<symbols>
<symbol name="FRAME_A_L">
<frame x1="0" y1="0" x2="279.4" y2="215.9" columns="6" rows="5" layer="94" border-bottom="no"/>
</symbol>
<symbol name="DOCFIELD">
<wire x1="0" y1="0" x2="71.12" y2="0" width="0.1016" layer="94"/>
<wire x1="101.6" y1="15.24" x2="87.63" y2="15.24" width="0.1016" layer="94"/>
<wire x1="0" y1="0" x2="0" y2="5.08" width="0.1016" layer="94"/>
<wire x1="0" y1="5.08" x2="71.12" y2="5.08" width="0.1016" layer="94"/>
<wire x1="0" y1="5.08" x2="0" y2="15.24" width="0.1016" layer="94"/>
<wire x1="101.6" y1="15.24" x2="101.6" y2="5.08" width="0.1016" layer="94"/>
<wire x1="71.12" y1="5.08" x2="71.12" y2="0" width="0.1016" layer="94"/>
<wire x1="71.12" y1="5.08" x2="87.63" y2="5.08" width="0.1016" layer="94"/>
<wire x1="71.12" y1="0" x2="101.6" y2="0" width="0.1016" layer="94"/>
<wire x1="87.63" y1="15.24" x2="87.63" y2="5.08" width="0.1016" layer="94"/>
<wire x1="87.63" y1="15.24" x2="0" y2="15.24" width="0.1016" layer="94"/>
<wire x1="87.63" y1="5.08" x2="101.6" y2="5.08" width="0.1016" layer="94"/>
<wire x1="101.6" y1="5.08" x2="101.6" y2="0" width="0.1016" layer="94"/>
<wire x1="0" y1="15.24" x2="0" y2="22.86" width="0.1016" layer="94"/>
<wire x1="101.6" y1="35.56" x2="0" y2="35.56" width="0.1016" layer="94"/>
<wire x1="101.6" y1="35.56" x2="101.6" y2="22.86" width="0.1016" layer="94"/>
<wire x1="0" y1="22.86" x2="101.6" y2="22.86" width="0.1016" layer="94"/>
<wire x1="0" y1="22.86" x2="0" y2="35.56" width="0.1016" layer="94"/>
<wire x1="101.6" y1="22.86" x2="101.6" y2="15.24" width="0.1016" layer="94"/>
<text x="1.27" y="1.27" size="2.54" layer="94">Date:</text>
<text x="12.7" y="1.27" size="2.54" layer="94">&gt;LAST_DATE_TIME</text>
<text x="72.39" y="1.27" size="2.54" layer="94">Sheet:</text>
<text x="86.36" y="1.27" size="2.54" layer="94">&gt;SHEET</text>
<text x="88.9" y="11.43" size="2.54" layer="94">REV:</text>
<text x="1.27" y="19.05" size="2.54" layer="94">TITLE:</text>
<text x="1.27" y="11.43" size="2.54" layer="94">Document Number:</text>
<text x="17.78" y="19.05" size="2.54" layer="94">&gt;DRAWING_NAME</text>
</symbol>
</symbols>
<devicesets>
<deviceset name="FRAME_A_L" prefix="FRAME" uservalue="yes">
<description>&lt;b&gt;FRAME&lt;/b&gt; A Size , 8 1/2 x 11 INCH, Landscape&lt;p&gt;</description>
<gates>
<gate name="G$1" symbol="FRAME_A_L" x="0" y="0" addlevel="always"/>
<gate name="G$2" symbol="DOCFIELD" x="172.72" y="0" addlevel="always"/>
</gates>
<devices>
<device name="">
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
</libraries>
<attributes>
</attributes>
<variantdefs>
</variantdefs>
<classes>
<class number="0" name="default" width="0" drill="0">
</class>
</classes>
<parts>
<part name="FRAME1" library="frames" deviceset="FRAME_A_L" device=""/>
</parts>
<sheets>
<sheet>
<plain>
<text x="158.115" y="-20.32" size="2.54" layer="91">Questions, Call Dave @ (306)421-1443</text>
<text x="147.32" y="27.94" size="1.9304" layer="91">11" to center from back edge</text>
<circle x="100.965" y="55.88" radius="39.37" width="0.1524" layer="91"/>
<text x="75.565" y="12.065" size="1.9304" layer="91">6.375" R</text>
<text x="69.85" y="102.87" size="1.9304" layer="91">13" Radius</text>
<text x="96.52" y="-7.62" size="1.9304" layer="91">39.75" Wide</text>
<text x="205.105" y="53.34" size="1.9304" layer="91">18.5" deep</text>
<circle x="100.33" y="55.88" radius="71.12" width="0.1524" layer="91"/>
</plain>
<instances>
<instance part="FRAME1" gate="G$1" x="-31.75" y="-46.99"/>
<instance part="FRAME1" gate="G$2" x="140.97" y="-46.99"/>
</instances>
<busses>
</busses>
<nets>
<net name="N$1" class="0">
<segment>
<wire x1="0" y1="0" x2="152.4" y2="0" width="0.1524" layer="91"/>
<wire x1="152.4" y1="0" x2="201.93" y2="0" width="0.1524" layer="91"/>
<wire x1="201.93" y1="0" x2="201.93" y2="93.98" width="0.1524" layer="91"/>
<wire x1="201.93" y1="93.98" x2="160.401" y2="93.98" width="0.1524" layer="91"/>
<wire x1="0" y1="93.98" x2="0" y2="0" width="0.1524" layer="91"/>
<wire x1="152.4" y1="0" x2="152.4" y2="26.035" width="0.1524" layer="91"/>
<wire x1="151.13" y1="1.27" x2="152.4" y2="0" width="0.1524" layer="91"/>
<wire x1="152.4" y1="0" x2="153.67" y2="1.27" width="0.1524" layer="91"/>
<wire x1="40.259" y1="93.98" x2="40.2082" y2="93.98" width="0.1524" layer="91"/>
<wire x1="0" y1="93.98" x2="40.2082" y2="93.98" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$2" class="0">
<segment>
<wire x1="155.575" y1="93.98" x2="48.26" y2="94.615" width="0.1524" layer="91" curve="108.795611"/>
</segment>
</net>
<net name="N$3" class="0">
<segment>
<wire x1="96.52" y1="55.88" x2="105.41" y2="55.88" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$4" class="0">
<segment>
<wire x1="100.965" y1="59.69" x2="100.965" y2="52.07" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$7" class="0">
<segment>
<wire x1="107.95" y1="55.88" x2="152.4" y2="55.88" width="0.1524" layer="91"/>
<wire x1="152.4" y1="55.88" x2="152.4" y2="31.75" width="0.1524" layer="91"/>
<wire x1="109.22" y1="57.15" x2="107.95" y2="55.88" width="0.1524" layer="91"/>
<wire x1="107.95" y1="55.88" x2="109.22" y2="54.61" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$5" class="0">
<segment>
<wire x1="74.295" y1="12.7" x2="61.595" y2="12.7" width="0.1524" layer="91"/>
<wire x1="61.595" y1="12.7" x2="61.595" y2="54.61" width="0.1524" layer="91"/>
<wire x1="61.595" y1="54.61" x2="61.595" y2="55.88" width="0.1524" layer="91"/>
<wire x1="73.025" y1="13.97" x2="74.295" y2="12.7" width="0.1524" layer="91"/>
<wire x1="74.295" y1="12.7" x2="73.025" y2="11.43" width="0.1524" layer="91"/>
<wire x1="62.865" y1="52.705" x2="61.595" y2="54.61" width="0.1524" layer="91"/>
<wire x1="61.595" y1="54.61" x2="60.325" y2="52.705" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$6" class="0">
<segment>
<wire x1="100.965" y1="12.7" x2="100.965" y2="49.53" width="0.1524" layer="91"/>
<wire x1="100.965" y1="12.7" x2="86.995" y2="12.7" width="0.1524" layer="91"/>
<wire x1="88.265" y1="13.97" x2="86.995" y2="12.7" width="0.1524" layer="91"/>
<wire x1="86.995" y1="12.7" x2="88.265" y2="11.43" width="0.1524" layer="91"/>
<wire x1="100.965" y1="49.53" x2="99.695" y2="48.26" width="0.1524" layer="91"/>
<wire x1="100.965" y1="49.53" x2="102.235" y2="48.26" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$8" class="0">
<segment>
<wire x1="101.6" y1="121.92" x2="74.93" y2="121.92" width="0.1524" layer="91"/>
<wire x1="74.93" y1="121.92" x2="74.93" y2="106.045" width="0.1524" layer="91"/>
<wire x1="100.33" y1="123.19" x2="101.6" y2="121.92" width="0.1524" layer="91"/>
<wire x1="101.6" y1="121.92" x2="100.33" y2="120.65" width="0.1524" layer="91"/>
<wire x1="73.66" y1="107.315" x2="74.93" y2="106.045" width="0.1524" layer="91"/>
<wire x1="74.93" y1="106.045" x2="76.2" y2="107.315" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$9" class="0">
<segment>
<wire x1="74.93" y1="101.6" x2="74.93" y2="55.88" width="0.1524" layer="91"/>
<wire x1="74.93" y1="55.88" x2="94.615" y2="55.88" width="0.1524" layer="91"/>
<wire x1="93.345" y1="57.15" x2="94.615" y2="55.88" width="0.1524" layer="91"/>
<wire x1="94.615" y1="55.88" x2="93.345" y2="54.61" width="0.1524" layer="91"/>
<wire x1="73.66" y1="100.33" x2="74.93" y2="101.6" width="0.1524" layer="91"/>
<wire x1="74.93" y1="101.6" x2="76.2" y2="100.33" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$10" class="0">
<segment>
<wire x1="0" y1="-2.54" x2="0" y2="-6.985" width="0.1524" layer="91"/>
<wire x1="0" y1="-6.985" x2="93.345" y2="-6.985" width="0.1524" layer="91"/>
<wire x1="92.075" y1="-5.715" x2="93.345" y2="-6.985" width="0.1524" layer="91"/>
<wire x1="93.345" y1="-6.985" x2="92.075" y2="-8.255" width="0.1524" layer="91"/>
<wire x1="-1.27" y1="-3.81" x2="0" y2="-2.54" width="0.1524" layer="91"/>
<wire x1="0" y1="-2.54" x2="1.27" y2="-3.81" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$11" class="0">
<segment>
<wire x1="201.93" y1="-6.985" x2="201.93" y2="-2.54" width="0.1524" layer="91"/>
<wire x1="114.935" y1="-6.985" x2="201.93" y2="-6.985" width="0.1524" layer="91"/>
<wire x1="116.205" y1="-5.715" x2="114.935" y2="-6.985" width="0.1524" layer="91"/>
<wire x1="114.935" y1="-6.985" x2="116.205" y2="-8.255" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$12" class="0">
<segment>
<wire x1="204.47" y1="0" x2="207.645" y2="0" width="0.1524" layer="91"/>
<wire x1="207.645" y1="0" x2="207.645" y2="49.53" width="0.1524" layer="91"/>
<wire x1="206.375" y1="48.26" x2="207.645" y2="49.53" width="0.1524" layer="91"/>
<wire x1="207.645" y1="49.53" x2="208.915" y2="48.26" width="0.1524" layer="91"/>
<wire x1="205.74" y1="1.27" x2="204.47" y2="0" width="0.1524" layer="91"/>
<wire x1="204.47" y1="0" x2="205.74" y2="-1.27" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$13" class="0">
<segment>
<wire x1="203.835" y1="93.98" x2="207.645" y2="93.98" width="0.1524" layer="91"/>
<wire x1="207.645" y1="58.42" x2="207.645" y2="93.98" width="0.1524" layer="91"/>
<wire x1="206.375" y1="59.69" x2="207.645" y2="58.42" width="0.1524" layer="91"/>
<wire x1="207.645" y1="58.42" x2="208.915" y2="59.69" width="0.1524" layer="91"/>
<wire x1="205.105" y1="92.71" x2="203.835" y2="93.98" width="0.1524" layer="91"/>
<wire x1="203.835" y1="93.98" x2="205.105" y2="95.25" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$14" class="0">
<segment>
<wire x1="200.66" y1="-3.81" x2="201.93" y2="-2.54" width="0.1524" layer="91"/>
<wire x1="201.93" y1="-2.54" x2="203.2" y2="-3.81" width="0.1524" layer="91"/>
</segment>
</net>
</nets>
</sheet>
</sheets>
</schematic>
</drawing>
</eagle>
