<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE eagle SYSTEM "eagle.dtd">
<eagle version="7.2.0">
<drawing>
<settings>
<setting alwaysvectorfont="no"/>
<setting verticaltext="up"/>
</settings>
<grid distance="0.1" unitdist="inch" unit="inch" style="lines" multiple="1" display="no" altdistance="0.01" altunitdist="inch" altunit="inch"/>
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
<library name="SamacSys_Parts">
<description>&lt;b&gt;https://componentsearchengine.com&lt;/b&gt;&lt;p&gt;
&lt;author&gt;Created by SamacSys&lt;/author&gt;</description>
<packages>
<package name="EX-PACKAGE">
<description>&lt;b&gt;EX-Package&lt;/b&gt;&lt;br&gt;
</description>
<smd name="1" x="-1.35" y="0.5" dx="1.27" dy="0.8" layer="1"/>
<smd name="2" x="-1.35" y="-0.5" dx="1.27" dy="0.8" layer="1"/>
<smd name="3" x="0.15" y="-1.45" dx="0.85" dy="0.3" layer="1" rot="R90"/>
<smd name="4" x="0.65" y="-1.45" dx="0.85" dy="0.3" layer="1" rot="R90"/>
<smd name="5" x="1.35" y="-0.75" dx="0.85" dy="0.3" layer="1"/>
<smd name="6" x="1.35" y="-0.25" dx="0.85" dy="0.3" layer="1"/>
<smd name="7" x="1.35" y="0.25" dx="0.85" dy="0.3" layer="1"/>
<smd name="8" x="1.35" y="0.75" dx="0.85" dy="0.3" layer="1"/>
<smd name="9" x="0.65" y="1.45" dx="0.85" dy="0.3" layer="1" rot="R90"/>
<smd name="10" x="0.15" y="1.45" dx="0.85" dy="0.3" layer="1" rot="R90"/>
<text x="-0.37331875" y="0.065040625" size="1.27" layer="25" align="center">&gt;NAME</text>
<text x="-0.37331875" y="0.065040625" size="1.27" layer="27" align="center">&gt;VALUE</text>
<wire x1="-1.5" y1="1.5" x2="1.5" y2="1.5" width="0.254" layer="51"/>
<wire x1="1.5" y1="1.5" x2="1.5" y2="-1.5" width="0.254" layer="51"/>
<wire x1="1.5" y1="-1.5" x2="-1.5" y2="-1.5" width="0.254" layer="51"/>
<wire x1="-1.5" y1="-1.5" x2="-1.5" y2="1.5" width="0.254" layer="51"/>
<wire x1="-1.5" y1="1.5" x2="-0.3" y2="1.5" width="0.254" layer="21"/>
<wire x1="-1.5" y1="-1.5" x2="-0.3" y2="-1.5" width="0.254" layer="21"/>
<wire x1="1.5" y1="1.5" x2="1.12" y2="1.5" width="0.254" layer="21"/>
<wire x1="1.5" y1="-1.5" x2="1.12" y2="-1.5" width="0.254" layer="21"/>
<wire x1="-1.5" y1="1.5" x2="-1.5" y2="1.225" width="0.254" layer="21"/>
<wire x1="-1.5" y1="-1.5" x2="-1.5" y2="-1.225" width="0.254" layer="21"/>
<circle x="-2.197" y="0.513" radius="0.029" width="0.254" layer="25"/>
</package>
</packages>
<symbols>
<symbol name="ACS711KEXLT-15AB-T">
<wire x1="5.08" y1="2.54" x2="25.4" y2="2.54" width="0.254" layer="94"/>
<wire x1="25.4" y1="-12.7" x2="25.4" y2="2.54" width="0.254" layer="94"/>
<wire x1="25.4" y1="-12.7" x2="5.08" y2="-12.7" width="0.254" layer="94"/>
<wire x1="5.08" y1="2.54" x2="5.08" y2="-12.7" width="0.254" layer="94"/>
<text x="26.67" y="7.62" size="1.778" layer="95" align="center-left">&gt;NAME</text>
<text x="26.67" y="5.08" size="1.778" layer="96" align="center-left">&gt;VALUE</text>
<pin name="IP+" x="0" y="0" length="middle"/>
<pin name="IP-" x="0" y="-2.54" length="middle"/>
<pin name="GND" x="0" y="-5.08" length="middle"/>
<pin name="!FAULT" x="0" y="-7.62" length="middle"/>
<pin name="NC1" x="0" y="-10.16" length="middle"/>
<pin name="NC2" x="30.48" y="0" length="middle" rot="R180"/>
<pin name="NC3" x="30.48" y="-2.54" length="middle" rot="R180"/>
<pin name="NC4" x="30.48" y="-5.08" length="middle" rot="R180"/>
<pin name="VOUT" x="30.48" y="-7.62" length="middle" rot="R180"/>
<pin name="VCC" x="30.48" y="-10.16" length="middle" rot="R180"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="ACS711KEXLT-15AB-T" prefix="IC">
<description>&lt;b&gt;Hall Effect Linear Current Sensor with Overcurrent Fault Output for &lt;100 V Isolation Applications&lt;/b&gt;&lt;p&gt;
Source: &lt;a href="https://www.arrow.com/en/products/acs711kexlt-15ab-t/allegro-microsystems"&gt; Datasheet &lt;/a&gt;</description>
<gates>
<gate name="G$1" symbol="ACS711KEXLT-15AB-T" x="0" y="0"/>
</gates>
<devices>
<device name="" package="EX-PACKAGE">
<connects>
<connect gate="G$1" pin="!FAULT" pad="4"/>
<connect gate="G$1" pin="GND" pad="3"/>
<connect gate="G$1" pin="IP+" pad="1"/>
<connect gate="G$1" pin="IP-" pad="2"/>
<connect gate="G$1" pin="NC1" pad="5"/>
<connect gate="G$1" pin="NC2" pad="6"/>
<connect gate="G$1" pin="NC3" pad="7"/>
<connect gate="G$1" pin="NC4" pad="8"/>
<connect gate="G$1" pin="VCC" pad="10"/>
<connect gate="G$1" pin="VOUT" pad="9"/>
</connects>
<technologies>
<technology name="">
<attribute name="ARROW_PART_NUMBER" value="ACS711KEXLT-15AB-T" constant="no"/>
<attribute name="DESCRIPTION" value="Hall Effect Linear Current Sensor with Overcurrent Fault Output for &lt;100 V Isolation Applications" constant="no"/>
<attribute name="HEIGHT" value="mm" constant="no"/>
<attribute name="MANUFACTURER_NAME" value="Allegro Microsystems" constant="no"/>
<attribute name="MANUFACTURER_PART_NUMBER" value="ACS711KEXLT-15AB-T" constant="no"/>
</technology>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="Stuff_I_Use">
<packages>
<package name="CONN-KF2EDG-10(5.08)">
<description>Pad wth 1.6 mm Hole</description>
<hole x="-22.4" y="3" drill="1.6"/>
<pad name="PAD1" x="23.32" y="3" drill="1.6" diameter="3.81" shape="long" rot="R270"/>
<pad name="PAD2" x="18.24" y="3" drill="1.6" diameter="3.81" shape="long" rot="R270"/>
<hole x="13.16" y="3" drill="1.6"/>
<pad name="PAD3" x="13.16" y="3" drill="1.6" diameter="3.81" shape="long" rot="R270"/>
<pad name="PAD4" x="8.08" y="3" drill="1.6" diameter="3.81" shape="long" rot="R270"/>
<pad name="PAD5" x="3" y="3" drill="1.6" diameter="3.81" shape="long" rot="R270"/>
<pad name="PAD6" x="-2.08" y="3" drill="1.6" diameter="3.81" shape="long" rot="R270"/>
<pad name="PAD7" x="-7.16" y="3" drill="1.6" diameter="3.81" shape="long" rot="R270"/>
<pad name="PAD8" x="-12.24" y="3" drill="1.6" diameter="3.81" shape="long" rot="R270"/>
<pad name="PAD9" x="-17.32" y="3" drill="1.6" diameter="3.81" shape="long" rot="R270"/>
<pad name="PAD10" x="-22.4" y="3" drill="1.6" diameter="3.81" shape="long" rot="R270"/>
<hole x="18.24" y="3" drill="1.6"/>
<hole x="23.32" y="3" drill="1.6"/>
<hole x="3" y="3" drill="1.6"/>
<hole x="-2.08" y="3" drill="1.6"/>
<hole x="8.08" y="3" drill="1.6"/>
<hole x="-7.16" y="3" drill="1.6"/>
<hole x="-12.24" y="3" drill="1.6"/>
<hole x="-17.32" y="3" drill="1.6"/>
<circle x="23.32" y="0.46" radius="1.27" width="0" layer="21"/>
<wire x1="26" y1="6" x2="26" y2="-6" width="0.127" layer="51"/>
<wire x1="26" y1="-6" x2="-25" y2="-6" width="0.127" layer="51"/>
<wire x1="-25" y1="-6" x2="-25" y2="6" width="0.127" layer="51"/>
<wire x1="-25" y1="6" x2="26" y2="6" width="0.127" layer="51"/>
<text x="5" y="-4" size="1.27" layer="51" rot="R180">Board Edge</text>
<wire x1="-25" y1="-6" x2="-25" y2="6" width="0.3048" layer="21"/>
<wire x1="-25" y1="6" x2="26" y2="6" width="0.3048" layer="21"/>
<wire x1="26" y1="6" x2="26" y2="-6" width="0.3048" layer="21"/>
<wire x1="26" y1="-6" x2="-25" y2="-6" width="0.3048" layer="21"/>
<text x="-24.54" y="-3" size="1.27" layer="25">&gt;NAME</text>
<text x="-16.86" y="-3" size="1.27" layer="25">&gt;VALUE</text>
</package>
</packages>
<symbols>
<symbol name="CONN-KF2EDG-10(5.08)">
<pin name="P$1" x="-20.32" y="5.08" length="middle" rot="R270"/>
<pin name="P$2" x="-15.24" y="5.08" length="middle" rot="R270"/>
<pin name="P$3" x="-10.16" y="5.08" length="middle" rot="R270"/>
<pin name="P$4" x="-5.08" y="5.08" length="middle" rot="R270"/>
<pin name="P$5" x="0" y="5.08" length="middle" rot="R270"/>
<pin name="P$6" x="5.08" y="5.08" length="middle" rot="R270"/>
<pin name="P$7" x="10.16" y="5.08" length="middle" rot="R270"/>
<pin name="P$8" x="15.24" y="5.08" length="middle" rot="R270"/>
<pin name="P$9" x="20.32" y="5.08" length="middle" rot="R270"/>
<pin name="P$10" x="25.4" y="5.08" length="middle" rot="R270"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="CONN-KF2EDG-10(5.08)">
<gates>
<gate name="G$1" symbol="CONN-KF2EDG-10(5.08)" x="20.32" y="0"/>
</gates>
<devices>
<device name="E-BAYPLUGGABLECONNECTORS" package="CONN-KF2EDG-10(5.08)">
<connects>
<connect gate="G$1" pin="P$1" pad="PAD1"/>
<connect gate="G$1" pin="P$10" pad="PAD10"/>
<connect gate="G$1" pin="P$2" pad="PAD2"/>
<connect gate="G$1" pin="P$3" pad="PAD3"/>
<connect gate="G$1" pin="P$4" pad="PAD4"/>
<connect gate="G$1" pin="P$5" pad="PAD5"/>
<connect gate="G$1" pin="P$6" pad="PAD6"/>
<connect gate="G$1" pin="P$7" pad="PAD7"/>
<connect gate="G$1" pin="P$8" pad="PAD8"/>
<connect gate="G$1" pin="P$9" pad="PAD9"/>
</connects>
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
<part name="IC1" library="SamacSys_Parts" deviceset="ACS711KEXLT-15AB-T" device=""/>
<part name="IC2" library="SamacSys_Parts" deviceset="ACS711KEXLT-15AB-T" device=""/>
<part name="U$1" library="Stuff_I_Use" deviceset="CONN-KF2EDG-10(5.08)" device="E-BAYPLUGGABLECONNECTORS"/>
</parts>
<sheets>
<sheet>
<plain>
<frame x1="0" y1="0" x2="266.7" y2="203.2" columns="8" rows="5" layer="91"/>
</plain>
<instances>
<instance part="IC1" gate="G$1" x="104.14" y="157.48" rot="R270"/>
<instance part="IC2" gate="G$1" x="147.32" y="157.48" rot="R270"/>
<instance part="U$1" gate="G$1" x="121.92" y="185.42"/>
</instances>
<busses>
</busses>
<nets>
</nets>
</sheet>
</sheets>
</schematic>
</drawing>
</eagle>
