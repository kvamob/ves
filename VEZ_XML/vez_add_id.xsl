<?xml version="1.0" encoding="windows-1251"?>
<!--
  *****************************************************************
  ** Просматривает входной документ и добавляет атрибуты id
  ** в элементы <profil> и <curve>
  ** id генерируется XSLT-функцией generate-id()
  **
  ** Перед вызовом преобразования нужно добавить атрибут id
  ** в элемент <area> 
  *****************************************************************
-->
<xsl:stylesheet 
  version="1.0" 
  xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

<xsl:output method="xml" encoding="windows-1251" indent="no"/>

<xsl:template match="@*|node()">
    <xsl:copy>
       <xsl:apply-templates select="@*|node()"/>
    </xsl:copy>
</xsl:template>
<!--
<xsl:template match="area">
    <xsl:copy>
       <xsl:attribute name="id">
         <xsl:value-of select="generate-id()" />
       </xsl:attribute> 
       <xsl:apply-templates select="@*|node()"/>
    </xsl:copy>
</xsl:template>
-->
<xsl:template match="profil">
    <xsl:copy>
       <xsl:attribute name="id">
         <xsl:variable name="prev" select="../@id" /> 
         <xsl:value-of select="concat( $prev,
                                       'pr', string(position()))" />
       </xsl:attribute> 
       <xsl:apply-templates select="@*|node()"/>
    </xsl:copy>
</xsl:template>

<xsl:template match="curve">
    <xsl:copy>
       <xsl:attribute name="id">
         <xsl:value-of select="generate-id()" />
       </xsl:attribute> 
       <xsl:apply-templates select="@*|node()"/>
    </xsl:copy>
</xsl:template>

</xsl:stylesheet>
