-- FUNCTION: public.fun_registrar_fecha_proyecto(bigint, bigint, character varying, character varying, integer, integer, integer, integer, integer, integer, character varying, character varying, integer, character varying)

-- DROP FUNCTION IF EXISTS public.fun_registrar_fecha_proyecto(bigint, bigint, character varying, character varying, integer, integer, integer, integer, integer, integer, character varying, character varying, integer, character varying);
-- SELECT fun_registrar_fecha_proyecto( '90329121'::BIGINT, '66202403'::BIGINT, 'cobrosproveedorintranet'::VARCHAR, 'PHPphpphp'::VARCHAR, '102'::INTEGER, '96'::INTEGER, '1'::INTEGER, '96'::INTEGER, '7'::INTEGER, '63'::INTEGER, '2024-03-05'::VARCHAR, '2024-03-13'::VARCHAR );

CREATE OR REPLACE FUNCTION public.fun_registrar_fecha_proyecto(
	bigint,
	bigint,
	character varying,
	character varying,
	integer,
	integer,
	integer,
	integer,
	integer,
	integer,
	character varying,
	character varying,
	integer,
	character varying)
    
	RETURNS smallint
    LANGUAGE 'plpgsql'
    COST 100
    VOLATILE PARALLEL UNSAFE
AS $BODY$

DECLARE
	lEmpleado 				ALIAS FOR $1;
	lIdpproyecto 			ALIAS FOR $2;
	sNomProyecto 			ALIAS FOR $3;
	sNomLenguaje 			ALIAS FOR $4;
	iNumOcurrencias 		ALIAS FOR $5;
	iNumPorSemana 			ALIAS FOR $6;
	iCanColaboradores 		ALIAS FOR $7;
	iTotSemanal 			ALIAS FOR $8;
	iTotDias 				ALIAS FOR $9;
	iTotHoras 				ALIAS FOR $10;
	sFecIniciaProyecto 		ALIAS FOR $11;
	sFecFinalizaProyecto	ALIAS FOR $12;
	iDiasLunVie 			ALIAS FOR $13;
	sFecFinLunVie			ALIAS FOR $14;
BEGIN	
	
	INSERT INTO public.tbl_registra_fecha_de_proyecto( num_empleado, id_proyecto, nom_proyecto, nom_lenguaje, num_ocurrencias, num_por_semana, can_colaboradores, tot_semanal, tot_dias, tot_horas, fec_inicia_proyecto, fec_finaliza_proyecto, tot_dias_lun_a_vie, fec_fin_proyecto_lun_a_vie )
	VALUES ($1::bigint, $2::bigint, $3::varchar, $4::varchar, $5::integer, $6::integer, $7::integer, $8::integer, $9::integer, $10::integer, $11::varchar, $12::varchar, $13::integer, $14::varchar );
	
	RETURN 1; --Inserto
	
END
$BODY$;
