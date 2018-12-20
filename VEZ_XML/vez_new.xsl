<?xml version="1.0" encoding="windows-1251"?>
<!--
************************************************************************
  Преобразование XML файла с кривыми ВЭЗ в HTML файл
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
   <span class="red"><b>Участок: </b></span>
     <xsl:value-of select="@name" /><br />
   <span class="red"><b>Описание: </b></span>
   <xsl:value-of select="areadescr[1]" /><br />
   <xsl:apply-templates select="profil" />
</xsl:template>

<xsl:template match="profil">
  <xsl:choose>

   <!--  Отдельные кривые, не принадлежащие профилям -->
   <xsl:when test="@type = 'curves'">
     <table border="1">
     <tr>
        <td colspan="2">
         <b>Отдельные кривые</b>
        </td>
     </tr>
          <xsl:apply-templates select="curves" />
     </table>
   </xsl:when>
  
   <!--  Кривые находятся на профиле -->
   <xsl:when test="@type = 'profil'">
     <br />
     <table border="1">
     <tr>
        <td colspan="2">
          <span class="blue">
          <b>Профиль: </b><xsl:value-of select="@name" /><br />
          <b>Описание профиля: </b><xsl:value-of select="profildescr[1]" /><br />
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
   <b>Кривая ВЭЗ:</b>
   <xsl:value-of select="@name" /><br />
   Описание:
   <xsl:value-of select="curvedescr" /><br />
   Дата:
   <xsl:value-of select="@date" /><br />
   Координаты: X=<xsl:value-of select="@x" /> Y=
   <xsl:value-of select="@y" /> Z=
   <xsl:value-of select="@z" /><br />
   Аппаратура:
   <xsl:value-of select="device" /><br />
   Оператор:
   <xsl:value-of select="operator" /><br />
   Вычислитель:
   <xsl:value-of select="calculator" /><br />
   Погода:
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

  <!-- Сформируем элемент вида <img src="imagefile.gif" /> > -->
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
      <td rowspan="2">AB/2, м</td>
      <td rowspan="2">MN/2, м</td>
      <td colspan="2">Кажущееся сопротивление, Омм</td>
    </tr>
    <tr class="hdr"> 
      <td>Измеренное</td>
      <td>Вычисленное</td>
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
   <b>Результат интерпретации:</b><br />
   <b>R.M.S. = <xsl:value-of select="../@rms" />%</b><br />
   <table>
    <tr class="hdr">
      <td>Номер слоя</td>
      <td>Мощность слоя, м</td>
      <td><xsl:text>Уд. сопрот., Омм</xsl:text></td>
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
