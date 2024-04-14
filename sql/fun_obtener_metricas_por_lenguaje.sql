-- FUNCTION: public.fun_obtener_metricas_por_lenguaje(character, character, character)

-- DROP FUNCTION IF EXISTS public.fun_obtener_metricas_por_lenguaje(character, character, character);
-- SELECT fun_obtener_metricas_por_lenguaje( 'PHP', 'DESARROLLO');
-- SELECT * FROM ctl_metricas_por_lenguaje;

CREATE OR REPLACE FUNCTION public.fun_obtener_metricas_por_lenguaje(
	character,
	character)
    RETURNS SETOF typ_metricas
    LANGUAGE 'plpgsql'
    COST 100
    VOLATILE PARALLEL UNSAFE
    ROWS 1000

AS $BODY$

DECLARE
	cNomCliente		ALIAS FOR $1;
	cLenguaje		ALIAS FOR $2;
	
	Metricas    typ_metricas;
	recMetricas	RECORD;
BEGIN

	-- SELECT * FROM ctl_metricas_por_lenguaje;
	FOR recMetricas IN
		SELECT migracion_meta, vulnerabilidades_meta FROM ctl_metricas_por_lenguaje WHERE nom_lenguaje = $1::character varying AND tip_actividad = $2::character varying
	LOOP
	
		Metricas.mig_meta := recMetricas.migracion_meta;
		Metricas.vul_meta := recMetricas.vulnerabilidades_meta;
		
		RETURN NEXT Metricas;
	END LOOP;
	
	RETURN;


END
$BODY$;
