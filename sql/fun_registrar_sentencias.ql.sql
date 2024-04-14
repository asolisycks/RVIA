-- SELECT fun_registrar_sentencias( '90329121'::BIGINT, 'ID'::VARCHAR,, 'ng'::VARCHAR, 'C:\temp\bito\uno\ng\ng\CIA.cpp'::VARCHAR, '12'::INTEGER, 'SELECT * FROM fun_registrar_sentencias( lNumColaborador, sNombreProyecto, sArchivo, iLinea, sSentencia);'::VARCHAR );

-- DROP FUNCTION fun_registrar_sentencias CASCADE;
-- SELECT * FROM tbl_registra_sentencias_ia;

CREATE OR REPLACE FUNCTION public.fun_registrar_sentencias(
	bigint,					-- Empleado
	character varying,		-- ID del proyecto
	character varying,		-- Nombre proyecto
	character varying,		-- Nombre de archivo
	integer,				-- Línea encontró sentencia
	character varying		-- Sentencia SQL encontrada
)
    RETURNS smallint
    LANGUAGE 'plpgsql'
    COST 100
    VOLATILE PARALLEL UNSAFE
AS $BODY$

DECLARE
	lNumEmpleado 	ALIAS FOR $1;
	sIdProyecto		ALIAS FOR $2;
	sProyecto		ALIAS FOR $3;
	sArchivo		ALIAS FOR $4;
	iLinea			ALIAS FOR $5;
	sSentencia		ALIAS FOR $6;
BEGIN	
	
	INSERT INTO public.tbl_registra_sentencias_ia( num_empleado, id_proyecto, nom_proyecto, nom_archivo, num_linea, dat_sentencia )
	VALUES ($1::bigint, $2::varchar, $3::varchar, $4::varchar, $5::integer, $6::varchar);
	
	RETURN 1; --Inserto
	
END
$BODY$;