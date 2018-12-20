<?xml version="1.0" encoding="windows-1251"?>
<!--
************************************************************************
  �������������� XML ����� � ������� ��� � HTML ����
************************************************************************
-->
<xsl:stylesheet 
  version="1.0" 
  xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

<xsl:output method="html" encoding="windows-1251" indent="yes"/>

<xsl:template match="/">
<html>
  <head>
    <title>VEZ XML</title>
    <link rel="stylesheet" href="stylesheet.css" type="text/css" />
  </head>
    <body>
       <xsl:apply-templates select="area" />
<!--        <xsl:apply-templates /> -->
    </body> 
</html>
</xsl:template>

<xsl:template match="area">
   <span class="red"><b>�������: </b></span>
     <xsl:value-of select="@name" /><br />
   <span class="red"><b>��������: </b></span>
   <xsl:value-of select="areadescr[1]" /><br />
   <xsl:apply-templates select="profil" />
</xsl:template>

<xsl:template match="profil">
  <xsl:choose>

   <!--  ��������� ������, �� ������������� �������� -->
   <xsl:when test="@type = 'curves'">
     <table border="1">
     <tr>
        <td colspan="2">
         <b>��������� ������</b>
        </td>
     </tr>
          <xsl:apply-templates select="curves" />
     </table>
   </xsl:when>
  
   <!--  ������ ��������� �� ������� -->
   <xsl:when test="@type = 'profil'">
     <br />
     <table border="1">
     <tr>
        <td colspan="2">
          <span class="blue">
          <b>�������: </b><xsl:value-of select="@name" /><br />
          <b>�������� �������: </b><xsl:value-of select="profildescr[1]" /><br />
          </span> 
        </td>
     </tr>
          <xsl:apply-templates select="curves" />
     </table>
   </xsl:when>

  </xsl:choose>
</xsl:template>

<xsl:template match="curves">
          <xsl:apply-templates select="curve" />
</xsl:template>

<xsl:template match="curve">
 <tr>
   <td valign="top"><b><xsl:value-of select="@name" /></b>
   <xsl:if test=" image != '' " >
      <xsl:apply-templates select="image" />
   </xsl:if> 
   </td>
 <td>  
   <b>������ ���:</b>
   <xsl:value-of select="@name" /><br />
   ��������:
   <xsl:value-of select="curvedescr" /><br />
   ����:
   <xsl:value-of select="@date" /><br />
   ����������: X=<xsl:value-of select="@x" /> Y=
   <xsl:value-of select="@y" /> Z=
   <xsl:value-of select="@z" /><br />
   ����������:
   <xsl:value-of select="device" /><br />
   ��������:
   <xsl:value-of select="operator" /><br />
   �����������:
   <xsl:value-of select="calculator" /><br />
   ������:
   <xsl:value-of select="weather" /><br />
<!--
   <xsl:if test=" image != '' " >
      <xsl:apply-templates select="image" />
   </xsl:if> 
-->
   <xsl:apply-templates select="samples" />
   <xsl:apply-templates select="layers" />
 </td>
 </tr>
</xsl:template>

<xsl:template match="image">
  <br />

  <!-- ���������� ������� ���� <img src="imagefile.gif" /> > -->
  <img src="none">
  <xsl:attribute name="src">
     <xsl:value-of select="." />
  </xsl:attribute>
  </img>

</xsl:template>

<xsl:template match="samples">
  <br />
  <table>
    <tr class="hdr"> 
      <td rowspan="2">AB/2, �</td>
      <td rowspan="2">MN/2, �</td>
      <td colspan="2">��������� �������������, ���</td>
    </tr>
    <tr class="hdr"> 
      <td>����������</td>
      <td>�����������</td>
    </tr>
      <xsl:apply-templates select="sample" />
</table>

</xsl:template>

<xsl:template match="sample">
   <tr>
      <td class="sample">
        <xsl:apply-templates select="@ab2" />
      </td>
      <td class="sample">
        <xsl:apply-templates select="@mn2" />
      </td>
      <td class="sample">
        <xsl:apply-templates select="@ro" />
      </td>
      <td class="sample">
        <xsl:apply-templates select="@rt" />
      </td>
   </tr>
</xsl:template>

<xsl:template match="layers">
   <br />
   <b>��������� �������������:</b><br />
   <b>R.M.S. = <xsl:value-of select="../@rms" />%</b><br />
   <table>
    <tr class="hdr">
      <td>����� ����</td>
      <td>�������� ����, �</td>
      <td><xsl:text>��. ������., ���</xsl:text></td>
    </tr>
    <xsl:apply-templates select="layer" />
   </table>
</xsl:template>

<xsl:template match="layer">
   <tr>
      <td class="sample">
        <xsl:apply-templates select="@id" />
      </td>
      <td class="sample">
        <xsl:apply-templates select="@h" />
      </td>
      <td class="sample">
        <xsl:apply-templates select="@r" />
      </td>
   </tr>
</xsl:template>

</xsl:stylesheet>
