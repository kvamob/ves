<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:xs="http://www.w3.org/2001/XMLSchema">
	<xsl:template match="/">
		<html>
			<head/>
			<body>
				<xsl:apply-templates/>
			</body>
		</html>
	</xsl:template>
	<xsl:template match="areadescr">
		<xsl:apply-templates/>
	</xsl:template>
	<xsl:template match="calculator">
		<xsl:apply-templates/>
	</xsl:template>
	<xsl:template match="profil">
		<span style="background-color:aqua; color:black">
			<xsl:apply-templates/>
		</span>
	</xsl:template>
</xsl:stylesheet>
