-- FUNCTION: public.fun_registrar_sentencias(bigint, bigint, character varying, character varying, integer, character varying)

-- DROP FUNCTION IF EXISTS public.fun_registrar_sentencias(bigint, bigint, character varying, character varying, integer, character varying);

-- SELECT fun_registrar_sentencias( '90329121'::BIGINT, '870202403'::BIGINT, 'intranet-master'::VARCHAR, 'C:\Temp\Bito\Intranet\fuentes\Botonera\intranet-master\actualizatkn.php'::VARCHAR, '11'::INTEGER, 'update intranet_administracion_token set intranet_administracion_token='$tokenssO' where intranet_administracion_token='".$_SESSION['G_token']."'";'::VARCHAR );

CREATE OR REPLACE FUNCTION public.fun_registrar_sentencias(
	bigint,
	bigint,
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
	lNumEmpleado 	ALIAS FOR $1;
	llIdProyecto	ALIAS FOR $2;
	sProyecto		ALIAS FOR $3;
	sArchivo		ALIAS FOR $4;
	iLinea			ALIAS FOR $5;
	sSentencia		ALIAS FOR $6;
BEGIN	
	
	INSERT INTO public.tbl_registra_sentencias_ia( num_empleado, id_proyecto, nom_proyecto, nom_archivo, num_linea, dat_sentencia )
	VALUES ($1::bigint, $2::bigint, $3::varchar, $4::varchar, $5::integer, $6::varchar);
	
	RETURN 1; --Inserto
	
END
$BODY$;

