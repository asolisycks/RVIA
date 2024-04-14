-----------------------------------------------------------------------------------------------------------------
--------------------------------------------- CONTROLES ---------------------------------------------------------
-- Table: public.cat_centros
-- DROP TABLE IF EXISTS public.cat_centros;

CREATE TABLE IF NOT EXISTS public.cat_centros
(
    num_centro integer NOT NULL,
    nom_centro character varying(50) COLLATE pg_catalog."default" NOT NULL,
    fec_movto timestamp without time zone NOT NULL DEFAULT now(),
    keyx integer NOT NULL DEFAULT nextval('cat_centros_keyx_seq'::regclass),
    CONSTRAINT pk_cat_centros PRIMARY KEY (keyx, num_centro),
    CONSTRAINT cat_centros_num_centro_key UNIQUE (num_centro)
)

TABLESPACE pg_default;

ALTER TABLE IF EXISTS public.cat_centros OWNER to sysdesarrollorvia;
GRANT ALL ON TABLE public.cat_centros TO sysdesarrollorvia;

COMMENT ON TABLE public.cat_centros IS 'Datos de los Centros';
COMMENT ON COLUMN public.cat_centros.num_centro IS 'Número del Centro (Primary Key)';
COMMENT ON COLUMN public.cat_centros.nom_centro IS 'Nombre del Centro';
COMMENT ON COLUMN public.cat_centros.fec_movto IS 'fecha de inserción del movimiento';
COMMENT ON COLUMN public.cat_centros.keyx IS 'Indicador automático consecutivo de la tabla (autoincremental)';

-- Index: idx_cat_centros_keyx
-- DROP INDEX IF EXISTS public.idx_cat_centros_keyx;

CREATE INDEX IF NOT EXISTS idx_cat_centros_keyx
    ON public.cat_centros USING btree
    (keyx ASC NULLS LAST)
    TABLESPACE pg_default;
-- Index: idx_cat_centros_nombrecentro
-- DROP INDEX IF EXISTS public.idx_cat_centros_nombrecentro;

CREATE INDEX IF NOT EXISTS idx_cat_centros_nombrecentro
    ON public.cat_centros USING btree
    (nom_centro COLLATE pg_catalog."default" ASC NULLS LAST)
    TABLESPACE pg_default;
-- Index: idx_cat_centros_numerocentro
-- DROP INDEX IF EXISTS public.idx_cat_centros_numerocentro;

CREATE INDEX IF NOT EXISTS idx_cat_centros_numerocentro
    ON public.cat_centros USING btree
    (num_centro ASC NULLS LAST)
    TABLESPACE pg_default;

------------------------------------------------------------------------------------------------------------------------------
-- Table: public.cat_colaboradores

-- DROP TABLE IF EXISTS public.cat_colaboradores;

CREATE TABLE IF NOT EXISTS public.cat_colaboradores
(
    num_colaborador bigint NOT NULL,
    nom_colaborador character varying(60) COLLATE pg_catalog."default" NOT NULL,
    num_puesto smallint NOT NULL,
    num_centro integer NOT NULL,
    num_proveedor smallint NOT NULL,
    num_gerente bigint NOT NULL,
    num_coordinador bigint NOT NULL,
    fec_movto timestamp without time zone NOT NULL DEFAULT now(),
    keyx integer NOT NULL DEFAULT nextval('cat_colaboradores_keyx_seq'::regclass),
    CONSTRAINT pk_cat_colaboradores PRIMARY KEY (keyx, num_colaborador),
    CONSTRAINT cat_colaboradores_num_colaborador_key UNIQUE (num_colaborador),
    CONSTRAINT fk_cat_colaboradores_cat_centros FOREIGN KEY (num_centro)
        REFERENCES public.cat_centros (num_centro) MATCH SIMPLE
        ON UPDATE NO ACTION
        ON DELETE NO ACTION,
    CONSTRAINT fk_cat_colaboradores_cat_coordinadores FOREIGN KEY (num_coordinador)
        REFERENCES public.cat_coordinadores (num_coordinador) MATCH SIMPLE
        ON UPDATE NO ACTION
        ON DELETE NO ACTION,
    CONSTRAINT fk_cat_colaboradores_cat_gerentes FOREIGN KEY (num_gerente)
        REFERENCES public.cat_gerentes (num_gerente) MATCH SIMPLE
        ON UPDATE NO ACTION
        ON DELETE NO ACTION,
    CONSTRAINT fk_cat_colaboradores_cat_proveedores FOREIGN KEY (num_proveedor)
        REFERENCES public.cat_proveedores (num_proveedor) MATCH SIMPLE
        ON UPDATE NO ACTION
        ON DELETE NO ACTION,
    CONSTRAINT fk_cat_colaboradores_cat_puestos FOREIGN KEY (num_puesto)
        REFERENCES public.cat_puestos (num_puesto) MATCH SIMPLE
        ON UPDATE NO ACTION
        ON DELETE NO ACTION
)

TABLESPACE pg_default;

ALTER TABLE IF EXISTS public.cat_colaboradores OWNER to sysdesarrollorvia;

GRANT ALL ON TABLE public.cat_colaboradores TO sysdesarrollorvia;

COMMENT ON TABLE public.cat_colaboradores IS 'Datos de los colaboradores involucrados en los proyectos';
COMMENT ON COLUMN public.cat_colaboradores.num_colaborador IS 'Número de empleado del colaborador  (Primary key)';
COMMENT ON COLUMN public.cat_colaboradores.nom_colaborador IS 'Nombre del colaborador';
COMMENT ON COLUMN public.cat_colaboradores.num_puesto IS 'Número de puesto al que pertenece el colaborador';
COMMENT ON COLUMN public.cat_colaboradores.num_centro IS 'Número de centro al que pertenece el colaborador';
COMMENT ON COLUMN public.cat_colaboradores.num_proveedor IS 'Número del proveedor al que pertenece el colaborador';
COMMENT ON COLUMN public.cat_colaboradores.num_gerente IS 'Número de gerente al que pertenece el colaborador';
COMMENT ON COLUMN public.cat_colaboradores.num_coordinador IS 'Número de coordinador al que pertenece el colaborador';
COMMENT ON COLUMN public.cat_colaboradores.fec_movto IS 'fecha de inserción del movimiento';
COMMENT ON COLUMN public.cat_colaboradores.keyx IS 'Indicador automático consecutivo de la tabla (autoincremental)';

-- Index: idx_cat_colaboradores_keyx
-- DROP INDEX IF EXISTS public.idx_cat_colaboradores_keyx;
CREATE INDEX IF NOT EXISTS idx_cat_colaboradores_keyx
    ON public.cat_colaboradores USING btree
    (keyx ASC NULLS LAST)
    TABLESPACE pg_default;

-- Index: idx_cat_colaboradores_nom_colaborador
-- DROP INDEX IF EXISTS public.idx_cat_colaboradores_nom_colaborador;
CREATE INDEX IF NOT EXISTS idx_cat_colaboradores_nom_colaborador
    ON public.cat_colaboradores USING btree
    (nom_colaborador COLLATE pg_catalog."default" ASC NULLS LAST)
    TABLESPACE pg_default;

-- Index: idx_cat_colaboradores_num_colaborador
-- DROP INDEX IF EXISTS public.idx_cat_colaboradores_num_colaborador;
CREATE INDEX IF NOT EXISTS idx_cat_colaboradores_num_colaborador
    ON public.cat_colaboradores USING btree
    (num_colaborador ASC NULLS LAST)
    TABLESPACE pg_default;

----------------------------------------------------------------------------------
-- Table: public.cat_coordinadores
-- DROP TABLE IF EXISTS public.cat_coordinadores;
CREATE TABLE IF NOT EXISTS public.cat_coordinadores
(
    num_coordinador bigint NOT NULL,
    nom_coordinador character varying(60) COLLATE pg_catalog."default" NOT NULL,
    fec_movto timestamp without time zone NOT NULL DEFAULT now(),
    keyx integer NOT NULL DEFAULT nextval('cat_coordinadores_keyx_seq'::regclass),
    CONSTRAINT pk_cat_coordinadores PRIMARY KEY (keyx, num_coordinador),
    CONSTRAINT cat_coordinadores_num_coordinador_key UNIQUE (num_coordinador)
)

TABLESPACE pg_default;

ALTER TABLE IF EXISTS public.cat_coordinadores OWNER to sysdesarrollorvia;

GRANT ALL ON TABLE public.cat_coordinadores TO sysdesarrollorvia;

COMMENT ON TABLE public.cat_coordinadores IS 'Datos de los Coordinadores involucrados en los proyectos';
COMMENT ON COLUMN public.cat_coordinadores.num_coordinador IS 'Número de empleado del Coordinador  (Primary key)';
COMMENT ON COLUMN public.cat_coordinadores.nom_coordinador IS 'Nombre del Coordinador';
COMMENT ON COLUMN public.cat_coordinadores.fec_movto IS 'fecha de inserción del movimiento';
COMMENT ON COLUMN public.cat_coordinadores.keyx IS 'Indicador automático consecutivo de la tabla (autoincremental)';

-- Index: idx_cat_coordinadores_keyx
-- DROP INDEX IF EXISTS public.idx_cat_coordinadores_keyx;
CREATE INDEX IF NOT EXISTS idx_cat_coordinadores_keyx
    ON public.cat_coordinadores USING btree
    (keyx ASC NULLS LAST)
    TABLESPACE pg_default;

-- Index: idx_cat_coordinadores_nom_coordinador
-- DROP INDEX IF EXISTS public.idx_cat_coordinadores_nom_coordinador;
CREATE INDEX IF NOT EXISTS idx_cat_coordinadores_nom_coordinador
    ON public.cat_coordinadores USING btree
    (nom_coordinador COLLATE pg_catalog."default" ASC NULLS LAST)
    TABLESPACE pg_default;

-- Index: idx_cat_coordinadores_num_coordinador
-- DROP INDEX IF EXISTS public.idx_cat_coordinadores_num_coordinador;
CREATE INDEX IF NOT EXISTS idx_cat_coordinadores_num_coordinador
    ON public.cat_coordinadores USING btree
    (num_coordinador ASC NULLS LAST)
    TABLESPACE pg_default;

----------------------------------------------------------------------------------

-- Table: public.cat_divisionales
-- DROP TABLE IF EXISTS public.cat_divisionales;
CREATE TABLE IF NOT EXISTS public.cat_divisionales
(
    num_divisional bigint NOT NULL,
    nom_divisional character varying(60) COLLATE pg_catalog."default" NOT NULL,
    fec_movto timestamp without time zone NOT NULL DEFAULT now(),
    keyx integer NOT NULL DEFAULT nextval('cat_divisionales_keyx_seq'::regclass),
    CONSTRAINT pk_cat_divisionales PRIMARY KEY (keyx, num_divisional),
    CONSTRAINT cat_divisionales_num_divisional_key UNIQUE (num_divisional)
)

TABLESPACE pg_default;

ALTER TABLE IF EXISTS public.cat_divisionales OWNER to sysdesarrollorvia;

GRANT ALL ON TABLE public.cat_divisionales TO sysdesarrollorvia;

COMMENT ON TABLE public.cat_divisionales IS 'Datos de los divisionales involucrados en los proyectos';
COMMENT ON COLUMN public.cat_divisionales.num_divisional IS 'Número de empleado del Divisional  (Primary key)';
COMMENT ON COLUMN public.cat_divisionales.nom_divisional IS 'Nombre del Divisional';
COMMENT ON COLUMN public.cat_divisionales.fec_movto IS 'fecha de inserción del movimiento';
COMMENT ON COLUMN public.cat_divisionales.keyx IS 'Indicador automático consecutivo de la tabla (autoincremental)';

-- Index: idx_cat_divisionales_keyx
-- DROP INDEX IF EXISTS public.idx_cat_divisionales_keyx;
CREATE INDEX IF NOT EXISTS idx_cat_divisionales_keyx
    ON public.cat_divisionales USING btree
    (keyx ASC NULLS LAST)
    TABLESPACE pg_default;

-- Index: idx_cat_divisionales_nom_divisional
-- DROP INDEX IF EXISTS public.idx_cat_divisionales_nom_divisional;
CREATE INDEX IF NOT EXISTS idx_cat_divisionales_nom_divisional
    ON public.cat_divisionales USING btree
    (nom_divisional COLLATE pg_catalog."default" ASC NULLS LAST)
    TABLESPACE pg_default;

-- Index: idx_cat_divisionales_num_divisional
-- DROP INDEX IF EXISTS public.idx_cat_divisionales_num_divisional;
CREATE INDEX IF NOT EXISTS idx_cat_divisionales_num_divisional
    ON public.cat_divisionales USING btree
    (num_divisional ASC NULLS LAST)
    TABLESPACE pg_default;

----------------------------------------------------------------------------------

-- Table: public.cat_gerentes
-- DROP TABLE IF EXISTS public.cat_gerentes;
CREATE TABLE IF NOT EXISTS public.cat_gerentes
(
    num_gerente bigint NOT NULL,
    nom_gerente character varying(60) COLLATE pg_catalog."default" NOT NULL,
    fec_movto timestamp without time zone NOT NULL DEFAULT now(),
    keyx integer NOT NULL DEFAULT nextval('cat_gerentes_keyx_seq'::regclass),
    CONSTRAINT pk_cat_gerentes PRIMARY KEY (keyx, num_gerente),
    CONSTRAINT cat_gerentes_num_gerente_key UNIQUE (num_gerente)
)

TABLESPACE pg_default;

ALTER TABLE IF EXISTS public.cat_gerentes OWNER to sysdesarrollorvia;

GRANT ALL ON TABLE public.cat_gerentes TO sysdesarrollorvia;

COMMENT ON COLUMN public.cat_gerentes.num_gerente IS 'Número de empleado del Gerente  (Primary key)';
COMMENT ON COLUMN public.cat_gerentes.nom_gerente IS 'Nombre del Gerente';
COMMENT ON COLUMN public.cat_gerentes.fec_movto IS 'fecha de inserción del movimiento';
COMMENT ON COLUMN public.cat_gerentes.keyx IS 'Indicador automático consecutivo de la tabla (autoincremental)';

-- Index: idx_cat_gerentes_keyx
-- DROP INDEX IF EXISTS public.idx_cat_gerentes_keyx;
CREATE INDEX IF NOT EXISTS idx_cat_gerentes_keyx
    ON public.cat_gerentes USING btree
    (keyx ASC NULLS LAST)
    TABLESPACE pg_default;

-- Index: idx_cat_gerentes_nom_gerente
-- DROP INDEX IF EXISTS public.idx_cat_gerentes_nom_gerente;
CREATE INDEX IF NOT EXISTS idx_cat_gerentes_nom_gerente
    ON public.cat_gerentes USING btree
    (nom_gerente COLLATE pg_catalog."default" ASC NULLS LAST)
    TABLESPACE pg_default;

-- Index: idx_cat_gerentes_num_gerente
-- DROP INDEX IF EXISTS public.idx_cat_gerentes_num_gerente;
CREATE INDEX IF NOT EXISTS idx_cat_gerentes_num_gerente
    ON public.cat_gerentes USING btree
    (num_gerente ASC NULLS LAST)
    TABLESPACE pg_default;

----------------------------------------------------------------------------------

-- Table: public.cat_nacionales
-- DROP TABLE IF EXISTS public.cat_nacionales;
CREATE TABLE IF NOT EXISTS public.cat_nacionales
(
    num_nacional bigint NOT NULL,
    nom_nacional character varying(60) COLLATE pg_catalog."default" NOT NULL,
    fec_movto timestamp without time zone NOT NULL DEFAULT now(),
    keyx integer NOT NULL DEFAULT nextval('cat_nacionales_keyx_seq'::regclass),
    CONSTRAINT pk_cat_nacionales PRIMARY KEY (keyx, num_nacional),
    CONSTRAINT cat_nacionales_num_nacional_key UNIQUE (num_nacional)
)

TABLESPACE pg_default;

ALTER TABLE IF EXISTS public.cat_nacionales OWNER to sysdesarrollorvia;

GRANT ALL ON TABLE public.cat_nacionales TO sysdesarrollorvia;

COMMENT ON TABLE public.cat_nacionales IS 'Datos de los Nacionales involucrados en los proyectos';
COMMENT ON COLUMN public.cat_nacionales.num_nacional IS 'Número de empleado del Nacional  (Primary key)';
COMMENT ON COLUMN public.cat_nacionales.nom_nacional IS 'Nombre del Nacional';
COMMENT ON COLUMN public.cat_nacionales.fec_movto IS 'fecha de inserción del movimiento';
COMMENT ON COLUMN public.cat_nacionales.keyx IS 'Indicador automático consecutivo de la tabla (autoincremental)';

-- Index: idx_cat_nacionales_keyx
-- DROP INDEX IF EXISTS public.idx_cat_nacionales_keyx;
CREATE INDEX IF NOT EXISTS idx_cat_nacionales_keyx
    ON public.cat_nacionales USING btree
    (keyx ASC NULLS LAST)
    TABLESPACE pg_default;

-- Index: idx_cat_nacionales_nom_nacional
-- DROP INDEX IF EXISTS public.idx_cat_nacionales_nom_nacional;
CREATE INDEX IF NOT EXISTS idx_cat_nacionales_nom_nacional
    ON public.cat_nacionales USING btree
    (nom_nacional COLLATE pg_catalog."default" ASC NULLS LAST)
    TABLESPACE pg_default;

-- Index: idx_cat_nacionales_num_nacional
-- DROP INDEX IF EXISTS public.idx_cat_nacionales_num_nacional;
CREATE INDEX IF NOT EXISTS idx_cat_nacionales_num_nacional
    ON public.cat_nacionales USING btree
    (num_nacional ASC NULLS LAST)
    TABLESPACE pg_default;

----------------------------------------------------------------------------------
-- Table: public.cat_proveedores

-- DROP TABLE IF EXISTS public.cat_proveedores;

CREATE TABLE IF NOT EXISTS public.cat_proveedores
(
    num_proveedor smallint NOT NULL,
    nom_proveedor character varying(50) COLLATE pg_catalog."default" NOT NULL,
    fec_movto timestamp without time zone NOT NULL DEFAULT now(),
    keyx integer NOT NULL DEFAULT nextval('cat_proveedores_keyx_seq'::regclass),
    CONSTRAINT pk_cat_proveedores PRIMARY KEY (keyx, num_proveedor),
    CONSTRAINT cat_proveedores_num_proveedor_key UNIQUE (num_proveedor)
)

TABLESPACE pg_default;

ALTER TABLE IF EXISTS public.cat_proveedores OWNER to sysdesarrollorvia;

GRANT ALL ON TABLE public.cat_proveedores TO sysdesarrollorvia;

COMMENT ON TABLE public.cat_proveedores IS 'Datos de los proveedores';
COMMENT ON COLUMN public.cat_proveedores.num_proveedor IS 'Número del Proveedor';
COMMENT ON COLUMN public.cat_proveedores.nom_proveedor IS 'Nombre del Proveedor';
COMMENT ON COLUMN public.cat_proveedores.fec_movto IS 'fecha de inserción del movimiento';
COMMENT ON COLUMN public.cat_proveedores.keyx IS 'Indicador automático consecutivo de la tabla (autoincremental)  (Primary key)';

-- Index: idx_cat_proveedores_keyx
-- DROP INDEX IF EXISTS public.idx_cat_proveedores_keyx;
CREATE INDEX IF NOT EXISTS idx_cat_proveedores_keyx
    ON public.cat_proveedores USING btree
    (keyx ASC NULLS LAST)
    TABLESPACE pg_default;

-- Index: idx_cat_proveedores_nom_proveedor
-- DROP INDEX IF EXISTS public.idx_cat_proveedores_nom_proveedor;
CREATE INDEX IF NOT EXISTS idx_cat_proveedores_nom_proveedor
    ON public.cat_proveedores USING btree
    (nom_proveedor COLLATE pg_catalog."default" ASC NULLS LAST)
    TABLESPACE pg_default;

-- Index: idx_cat_proveedores_num_proveedor
-- DROP INDEX IF EXISTS public.idx_cat_proveedores_num_proveedor;
CREATE INDEX IF NOT EXISTS idx_cat_proveedores_num_proveedor
    ON public.cat_proveedores USING btree
    (num_proveedor ASC NULLS LAST)
    TABLESPACE pg_default;

----------------------------------------------------------------------------------

-- Table: public.cat_puestos
-- DROP TABLE IF EXISTS public.cat_puestos;
CREATE TABLE IF NOT EXISTS public.cat_puestos
(
    num_puesto smallint NOT NULL,
    nom_puesto character varying(50) COLLATE pg_catalog."default" NOT NULL,
    fec_movto timestamp without time zone NOT NULL DEFAULT now(),
    keyx integer NOT NULL DEFAULT nextval('cat_puestos_keyx_seq'::regclass),
    CONSTRAINT pk_cat_puestos PRIMARY KEY (keyx, num_puesto),
    CONSTRAINT cat_puestos_num_puesto_key UNIQUE (num_puesto)
)

TABLESPACE pg_default;

ALTER TABLE IF EXISTS public.cat_puestos OWNER to sysdesarrollorvia;

GRANT ALL ON TABLE public.cat_puestos TO sysdesarrollorvia;

COMMENT ON TABLE public.cat_puestos IS 'Datos de los puestos';
COMMENT ON COLUMN public.cat_puestos.num_puesto IS 'Número del puesto (Primary Key)';
COMMENT ON COLUMN public.cat_puestos.nom_puesto IS 'Nombre del puesto';
COMMENT ON COLUMN public.cat_puestos.fec_movto IS 'fecha de inserción del movimiento';
COMMENT ON COLUMN public.cat_puestos.keyx IS 'Indicador automático consecutivo de la tabla (autoincremental)';

-- Index: idx_cat_puestos_keyx
-- DROP INDEX IF EXISTS public.idx_cat_puestos_keyx;
CREATE INDEX IF NOT EXISTS idx_cat_puestos_keyx
    ON public.cat_puestos USING btree
    (keyx ASC NULLS LAST)
    TABLESPACE pg_default;

-- Index: idx_cat_puestos_nom_puesto
-- DROP INDEX IF EXISTS public.idx_cat_puestos_nom_puesto;
CREATE INDEX IF NOT EXISTS idx_cat_puestos_nom_puesto
    ON public.cat_puestos USING btree
    (nom_puesto COLLATE pg_catalog."default" ASC NULLS LAST)
    TABLESPACE pg_default;

-- Index: idx_cat_puestos_num_puesto
-- DROP INDEX IF EXISTS public.idx_cat_puestos_num_puesto;
CREATE INDEX IF NOT EXISTS idx_cat_puestos_num_puesto
    ON public.cat_puestos USING btree
    (num_puesto ASC NULLS LAST)
    TABLESPACE pg_default;
    
----------------------------------------------------------------------------------

-- DROP TABLE IF EXISTS public.ctl_token_ia CASCADE;
-- SELECT * FROM ctl_token_ia;
-- TRUNCATE TABLE ctl_token_ia;
-- SELECT fun_registrar_token( '90329121'::BIGINT, '367cfa3ebdbbf8a41b0b4d57d213d82c96f1bbd95c9074a8aef33e7782eb456c'::VARCHAR );

CREATE TABLE IF NOT EXISTS public.ctl_token_ia
(
    num_empleado bigint NOT NULL,
    key_token character varying(200) COLLATE pg_catalog."default" NOT NULL,
	fec_expira timestamp NOT NULL,
    fec_movto timestamp  WITHOUT Time zone NOT NULL DEFAULT now(),
    keyx serial NOT NULL,
    CONSTRAINT pk_ctl_token_ia PRIMARY KEY (keyx)
) WITHOUT OIDS;

GRANT ALL ON TABLE public.ctl_token_ia TO syscheckattendancebyface;
GRANT ALL ON TABLE public.ctl_token_ia TO sysdesarrollorvia;

COMMENT ON TABLE public.ctl_token_ia IS 'Tabla de llaves por empleado';
COMMENT ON COLUMN public.ctl_token_ia.num_empleado IS 'Número de empleado de la persona que ejecutó la aplicación';
COMMENT ON COLUMN public.ctl_token_ia.key_token IS 'Token generado con duración de 72 hrs';
COMMENT ON COLUMN public.ctl_token_ia.fec_expira IS 'Fecha y hora de expiración del Token';
COMMENT ON COLUMN public.ctl_token_ia.fec_movto IS 'Fecha y hora (Se guarda en automático)';
COMMENT ON COLUMN public.ctl_token_ia.keyx IS 'Indicador automático consecutivo de la tabla (autoincremental) (Primary Key)';

 --index

CREATE INDEX idx_ctl_token_ia_num_empleado ON ctl_token_ia (num_empleado);
CREATE INDEX idx_ctl_token_ia_key_token ON ctl_token_ia (key_token);
CREATE INDEX idx_ctl_token_ia_fec_expira ON ctl_token_ia (fec_expira);
CREATE INDEX idx_ctl_token_ia_keyx ON ctl_token_ia (keyx);

-- SELECT * FROM ctl_token_ia;
-- SELECT num_empleado, key_token, fec_movto FROM ctl_token_ia WHERE num_empleado = '90329121'::bigint ORDER BY keyx DESC LIMIT 1;
-- SELECT key_token FROM ctl_token_ia WHERE num_empleado = '90329121'::bigint ORDER BY keyx DESC LIMIT 1;
-- SELECT public.fun_obtener_token('90329121'::bigint);

-- SELECT fun_obtener_token('90329121'::integer, '74846eb95f92432d6f623ee796e291d6810fef7a0bb1f8e42da4be686cd8f948'::character varying);
-----------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------------------
-- DROP TABLE IF EXISTS public.tbl_registra_totales;
-- SELECT * FROM tbl_registra_totales WHERE id_proyecto = 682202403;

CREATE TABLE IF NOT EXISTS public.tbl_registra_totales
(
    num_empleado bigint NOT NULL,
	id_proyecto bigint NOT NULL,
	nom_proyecto character varying(100) COLLATE pg_catalog."default" NOT NULL,
	nom_language character varying(30) COLLATE pg_catalog."default" NOT NULL,
	num_files integer NOT NULL,
	num_blank integer NOT NULL,
	num_comment integer NOT NULL,
	num_code integer NOT NULL,
	fec_movto timestamp without time zone NOT NULL DEFAULT now(),
    keyx serial NOT NULL,
    CONSTRAINT pk_tbl_registra_totales PRIMARY KEY (keyx)
) WITHOUT OIDS;

GRANT ALL ON TABLE public.tbl_registra_totales TO syscheckattendancebyface;
GRANT ALL ON TABLE public.tbl_registra_totales TO sysdesarrollorvia;

COMMENT ON TABLE public.tbl_registra_totales_checkmarx IS 'Datos de empleados y totales checkmarx de un proyecto';
COMMENT ON COLUMN public.tbl_registra_totales.num_empleado IS 'Número de empleado de la persona que ejecutó la aplicación';
COMMENT ON COLUMN public.tbl_registra_totales.id_proyecto IS 'ID del Proyecto';
COMMENT ON COLUMN public.tbl_registra_totales.nom_proyecto IS 'Nombre del Proyecto';
COMMENT ON COLUMN public.tbl_registra_totales.nom_language IS 'Nombre de los lenguajes encontrados en el proyecto';
COMMENT ON COLUMN public.tbl_registra_totales.num_files IS 'Número archivos por lenguaje encontrados en el proyecto';
COMMENT ON COLUMN public.tbl_registra_totales.num_blank IS 'Número líneas en blanco por lenguaje encontrados en el proyecto';
COMMENT ON COLUMN public.tbl_registra_totales.num_comment IS 'Número líneas de comentarios por lenguaje encontrados en el proyecto';
COMMENT ON COLUMN public.tbl_registra_totales.num_code IS 'Número de líneas de código por lenguaje encontrados en el proyecto';
COMMENT ON COLUMN public.tbl_registra_totales.fec_movto IS 'Fecha y hora de registro (guardada en automático)';
COMMENT ON COLUMN public.tbl_registra_totales.keyx IS 'Indicador automático consecutivo de la tabla (autoincremental) (Primary Key)';

 --index

CREATE INDEX idx_tbl_registra_totales_num_empleado ON tbl_registra_totales (num_empleado);
CREATE INDEX idx_tbl_registra_totales_id_proyecto ON tbl_registra_totales (id_proyecto);
CREATE INDEX idx_tbl_registra_totales_nom_proyecto ON tbl_registra_totales (nom_proyecto);
CREATE INDEX idx_tbl_registra_totales_nom_language ON tbl_registra_totales (nom_language);
CREATE INDEX idx_tbl_registra_totales_keyx ON tbl_registra_totales (keyx);

-- SELECT * FROM tbl_registra_totales;
-- TRUNCATE TABLE public.tbl_registra_totales;
-----------------------------------------------------------------------------------------------------------------------------

-- Table: public.tbl_registra_uso_ia

-- DROP TABLE IF EXISTS public.tbl_registra_sentencias_ia;
-- TRUNCATE TABLE public.tbl_registra_sentencias_ia;

-- SELECT * FROM tbl_registra_sentencias_ia WHERE id_proyecto = 682202403;;

CREATE TABLE IF NOT EXISTS public.tbl_registra_sentencias_ia
(
    num_empleado bigint NOT NULL,
	id_proyecto bigint NOT NULL,
	--id_proyecto character varying(100) COLLATE pg_catalog."default" NOT NULL,
    nom_proyecto character varying(100) COLLATE pg_catalog."default" NOT NULL,
    nom_archivo character varying(300) COLLATE pg_catalog."default" NOT NULL,
    num_linea integer NOT NULL,
    dat_sentencia character varying(1000) COLLATE pg_catalog."default" NOT NULL,
    fec_movto timestamp without time zone NOT NULL DEFAULT now(),
    keyx serial NOT NULL,
    CONSTRAINT pk_tbl_registra_sentencias_ia PRIMARY KEY (keyx)
) WITHOUT OIDS;

GRANT ALL ON TABLE public.tbl_registra_sentencias_ia TO syscheckattendancebyface;
GRANT ALL ON TABLE public.tbl_registra_sentencias_ia TO sysdesarrollorvia;

COMMENT ON TABLE public.tbl_registra_sentencias_ia IS 'Datos de empleados y sentencias encontradas en el parseo de un proyecto';
COMMENT ON COLUMN public.tbl_registra_sentencias_ia.num_empleado IS 'Número de empleado de la persona que ejecutó la aplicación';
COMMENT ON COLUMN public.tbl_registra_sentencias_ia.id_proyecto IS 'ID del Proyecto';
COMMENT ON COLUMN public.tbl_registra_sentencias_ia.nom_proyecto IS 'Nombre del Proyecto';
COMMENT ON COLUMN public.tbl_registra_sentencias_ia.nom_archivo IS 'Nombre de archivo al que pertenece el Colaborador';
COMMENT ON COLUMN public.tbl_registra_sentencias_ia.num_linea IS 'Número de línea donde se encontró a sentencia';
COMMENT ON COLUMN public.tbl_registra_sentencias_ia.dat_sentencia IS 'Sentencia encontrada en el archivo';
COMMENT ON COLUMN public.tbl_registra_sentencias_ia.fec_movto IS 'Fecha y hora de primer registro (guardada en automático)';
COMMENT ON COLUMN public.tbl_registra_sentencias_ia.keyx IS 'Indicador automático consecutivo de la tabla (autoincremental) (Primary Key)';

 --index

CREATE INDEX idx_tbl_registra_sentencias_ia_num_emppleado ON tbl_registra_sentencias_ia (num_empleado);
CREATE INDEX idx_tbl_registra_sentencias_ia_id_proyecto ON tbl_registra_sentencias_ia (id_proyecto);
CREATE INDEX idx_tbl_registra_sentencias_ia_nom_proyecto ON tbl_registra_sentencias_ia (nom_proyecto);
CREATE INDEX idx_tbl_registra_sentencias_ia_keyx ON tbl_registra_sentencias_ia (keyx);

-- SELECT * FROM tbl_registra_sentencias_ia;
----------------------------------------------------------------------------------------------------------------
-- DROP TABLE IF EXISTS public.tbl_registra_obsoletos_ia;
-- SELECT * FROM tbl_registra_obsoletos_ia WHERE id_proyecto = 682202403;;

CREATE TABLE IF NOT EXISTS public.tbl_registra_obsoletos_ia
(
    num_empleado bigint NOT NULL,
	id_proyecto bigint NOT NULL,
	-- id_proyecto character varying(100) COLLATE pg_catalog."default" NOT NULL,
    nom_proyecto character varying(100) COLLATE pg_catalog."default" NOT NULL,
    nom_archivo character varying(300) COLLATE pg_catalog."default" NOT NULL,
    num_linea integer NOT NULL,
    dat_obsoleto character varying(1000) COLLATE pg_catalog."default" NOT NULL,
    fec_movto timestamp without time zone NOT NULL DEFAULT now(),
    keyx serial NOT NULL,
    CONSTRAINT pk_tbl_registra_obsoletos_ia PRIMARY KEY (keyx)
) WITHOUT OIDS;

GRANT ALL ON TABLE public.tbl_registra_obsoletos_ia TO syscheckattendancebyface;
GRANT ALL ON TABLE public.tbl_registra_obsoletos_ia TO sysdesarrollorvia;

COMMENT ON TABLE public.tbl_registra_obsoletos_ia IS 'Datos de empleados y sentencias encontradas en el parseo de un proyecto';
COMMENT ON COLUMN public.tbl_registra_obsoletos_ia.num_empleado IS 'Número de empleado de la persona que ejecutó la aplicación';
COMMENT ON COLUMN public.tbl_registra_obsoletos_ia.id_proyecto IS 'ID del Proyecto';
COMMENT ON COLUMN public.tbl_registra_obsoletos_ia.nom_proyecto IS 'Nombre del Proyecto';
COMMENT ON COLUMN public.tbl_registra_obsoletos_ia.nom_archivo IS 'Nombre de archivo al que pertenece el Colaborador';
COMMENT ON COLUMN public.tbl_registra_obsoletos_ia.num_linea IS 'Número de línea donde se encontró a sentencia';
COMMENT ON COLUMN public.tbl_registra_obsoletos_ia.dat_obsoleto IS 'Sentencia encontrada en el archivo';
COMMENT ON COLUMN public.tbl_registra_obsoletos_ia.fec_movto IS 'Fecha y hora de primer registro (guardada en automático)';
COMMENT ON COLUMN public.tbl_registra_obsoletos_ia.keyx IS 'Indicador automático consecutivo de la tabla (autoincremental) (Primary Key)';

 --index

CREATE INDEX idx_tbl_registra_obsoletos_ia_num_emppleado ON tbl_registra_obsoletos_ia (num_empleado);
CREATE INDEX idx_tbl_registra_obsoletos_ia_id_proyecto ON tbl_registra_obsoletos_ia (id_proyecto);
CREATE INDEX idx_tbl_registra_obsoletos_ia_nom_proyecto ON tbl_registra_obsoletos_ia (nom_proyecto);
CREATE INDEX idx_tbl_registra_obsoletos_ia_keyx ON tbl_registra_obsoletos_ia (keyx);

-- SELECT * FROM tbl_registra_obsoletos_ia;
-- TRUNCATE TABLE public.tbl_registra_obsoletos_ia;
-----------------------------------------------------------------------------------------------------------------------------

-- LENGUAJE|OCURRENCIAS|X_SEMANA|CANT_COLAB|TOT_SEM|TOT_DIAS|TOT_HORAS|FECHA_INI|FECHA_FIN

------------------------------------------------------
--------------------- META SEMANAL ---------------------------------
-- DROP TABLE IF EXISTS public.ctl_prompt CASCADE;
-- SELECT * FROM ctl_prompt;
-- TRUNCATE TABLE ctl_prompt;

CREATE TABLE IF NOT EXISTS public.ctl_prompt
(
    nom_cliente_ia character(25) NOT NULL,
	ext_lenguaje character (20) COLLATE pg_catalog."default" NOT NULL,
    pmt_texto character varying(400000) COLLATE pg_catalog."default" NOT NULL,
	nom_model character (20) COLLATE pg_catalog."default" NOT NULL,
	flg_activo integer NOT NULL DEFAULT 0,
    fec_movto timestamp without time zone NOT NULL DEFAULT now(),
    keyx serial NOT NULL,
    CONSTRAINT pk_ctl_prompt PRIMARY KEY (keyx)
) WITHOUT OIDS;

GRANT ALL ON TABLE public.ctl_prompt TO syscheckattendancebyface;
GRANT ALL ON TABLE public.ctl_prompt TO sysdesarrollorvia;

COMMENT ON TABLE public.ctl_prompt IS 'Prompt generados para utilizar en losnuevos clientes de IA';
COMMENT ON COLUMN public.ctl_prompt.nom_cliente_ia IS 'Nombre del cliente de IA que se está utlizando';
COMMENT ON COLUMN public.ctl_prompt.ext_lenguaje IS 'Extensión del lenguaje de programación';
COMMENT ON COLUMN public.ctl_prompt.pmt_texto IS ' Prompt a utilizar en las inteligencias GPT4';
COMMENT ON COLUMN public.ctl_prompt.nom_model IS 'Se utiliza para identificar el modelo a utilizar, BASIC o ADVANCED';
COMMENT ON COLUMN public.ctl_prompt.flg_activo IS 'Se utiliza para identificar si el prompt está activo. 0 = Activo, 1 = Inactivo';
COMMENT ON COLUMN public.ctl_prompt.fec_movto IS 'Fecha y hora (guardada en automático)';
COMMENT ON COLUMN public.ctl_prompt.keyx IS 'Indicador automático consecutivo de la tabla (autoincremental) (Primary Key)';

 --index

CREATE INDEX idx_ctl_prompt_nom_cliente_ia ON ctl_prompt (nom_cliente_ia);
CREATE INDEX idx_ctl_prompt_ext_lenguaje ON ctl_prompt (ext_lenguaje);
CREATE INDEX idx_ctl_prompt_pmt_texto ON ctl_prompt (pmt_texto);
CREATE INDEX idx_ctl_prompt_nom_model ON ctl_prompt (nom_model);
CREATE INDEX idx_ctl_prompt_flg_activo ON ctl_prompt (flg_activo);
CREATE INDEX idx_ctl_prompt_fec_movto ON ctl_prompt (fec_movto);
CREATE INDEX idx_ctl_prompt_keyx ON ctl_prompt (keyx);

SELECT * FROM ctl_prompt ORDER BY keyx ASC;
SELECT pmt_texto FROM ctl_prompt WHERE nom_cliente_ia = 'BITO' AND ext_lenguaje = 'PHP' AND nom_model = 'ADVANCED' AND flg_activo = 0;

INSERT INTO ctl_prompt (nom_cliente_ia, ext_lenguaje, pmt_texto, nom_model) VALUES ('BITO', 'PHP', '<role>
You are an expert code review agent, with significant experience in code review. You get reward points, ranging from -5 to +5 for each problem you find; higher points are better. Youll get higher points for issues you consider high impact, save senior engineers a lot of time, catch issues that are hard to find through manual review, and significantly improve code quality. You can also be penalized with negative reward points if you report trivial problems that any junior developer can encounter, do not save time, and do not improve code quality significantly. While reviewing the code, your goal is to maximize your reward. Below you will find examples of high, medium, and low reward problems. This is not the complete list, but just some examples that you can learn from.
</role>
<reward>
-Syntax errors (0 points): Basic errors, often detected by automated tools. It is not a focus for human reviewers.
-Code formatting and style issues (1 point): Ensure consistency with project style guidelines.
-Variable naming problems (1 point): Inappropriate or unclear naming conventions.
-Comments and Documentation (2 points): Missing or unclear documentation.
-Code Duplication (3 points): Identify repeated blocks of code that can be refactored.
-Complex and illegible code (3 points): Code that is difficult to understand and maintain.
-Logic errors (4 points): Flaws in logic that could lead to incorrect behavior, but are not immediately obvious.
-Performance problems (4 points): Identify inefficient code that could slow down the system.
-Security vulnerabilities (5 points): Identify potential security risks, which requires experience and is crucial for the integrity of the code.
-Scalability issues (5 points): Identify code that may not scale well with increased load or data, which requires forethought and experience.
-Find trivial or non-existent problems (-1 to -2 points): point out problems that are non-existent or extremely minor.
-Misidentification of problems (-3 points): Incorrectly identifying something as a problem when it is not.
-Missin Critical Issues (-4 to -5 points): Failure to identify serious flaws such as major errors, security vulnerabilities or scalability problems.
</reward>
{{%code%}}
Issues: <Brief bulleted list of issues>
Fixed code: <Rewritten code between three quotes ```PHP at the beginning of the code and ``` at the end of the code.>', 'ADVANCED');

INSERT INTO ctl_prompt (nom_cliente_ia, ext_lenguaje, pmt_texto, nom_model)
VALUES ('BITO', 'C', '<role>
You are an expert code review agent, with significant experience in code review. You get reward points, ranging from -5 to +5 for each problem you find; higher points are better. Youll get higher points for issues you consider high impact, save senior engineers a lot of time, catch issues that are hard to find through manual review, and significantly improve code quality. You can also be penalized with negative reward points if you report trivial problems that any junior developer can encounter, do not save time, and do not improve code quality significantly. While reviewing the code, your goal is to maximize your reward. Below you will find examples of high, medium, and low reward problems. This is not the complete list, but just some examples that you can learn from.
</role>
<reward>
-Syntax errors (0 points): Basic errors, often detected by automated tools. It is not a focus for human reviewers.
-Code formatting and style issues (1 point): Ensure consistency with project style guidelines.
-Variable naming problems (1 point): Inappropriate or unclear naming conventions.
-Comments and Documentation (2 points): Missing or unclear documentation.
-Code Duplication (3 points): Identify repeated blocks of code that can be refactored.
-Complex and illegible code (3 points): Code that is difficult to understand and maintain.
-Logic errors (4 points): Flaws in logic that could lead to incorrect behavior, but are not immediately obvious.
-Performance problems (4 points): Identify inefficient code that could slow down the system.
-Security vulnerabilities (5 points): Identify potential security risks, which requires experience and is crucial for the integrity of the code.
-Scalability issues (5 points): Identify code that may not scale well with increased load or data, which requires forethought and experience.
-Find trivial or non-existent problems (-1 to -2 points): point out problems that are non-existent or extremely minor.
-Misidentification of problems (-3 points): Incorrectly identifying something as a problem when it is not.
-Missin Critical Issues (-4 to -5 points): Failure to identify serious flaws such as major errors, security vulnerabilities or scalability problems.
</reward>
{{%code%}}
Issues: <Brief bulleted list of issues>
Fixed code: <Rewritten code between three quotes ```C at the beginning of the code and ``` at the end of the code.>', 'ADVANCED');

INSERT INTO ctl_prompt (nom_cliente_ia, ext_lenguaje, pmt_texto, nom_model)
VALUES ('BITO', 'CPP', '<role>
You are an expert code review agent, with significant experience in code review. You get reward points, ranging from -5 to +5 for each problem you find; higher points are better. Youll get higher points for issues you consider high impact, save senior engineers a lot of time, catch issues that are hard to find through manual review, and significantly improve code quality. You can also be penalized with negative reward points if you report trivial problems that any junior developer can encounter, do not save time, and do not improve code quality significantly. While reviewing the code, your goal is to maximize your reward. Below you will find examples of high, medium, and low reward problems. This is not the complete list, but just some examples that you can learn from.
</role>
<reward>
-Syntax errors (0 points): Basic errors, often detected by automated tools. It is not a focus for human reviewers.
-Code formatting and style issues (1 point): Ensure consistency with project style guidelines.
-Variable naming problems (1 point): Inappropriate or unclear naming conventions.
-Comments and Documentation (2 points): Missing or unclear documentation.
-Code Duplication (3 points): Identify repeated blocks of code that can be refactored.
-Complex and illegible code (3 points): Code that is difficult to understand and maintain.
-Logic errors (4 points): Flaws in logic that could lead to incorrect behavior, but are not immediately obvious.
-Performance problems (4 points): Identify inefficient code that could slow down the system.
-Security vulnerabilities (5 points): Identify potential security risks, which requires experience and is crucial for the integrity of the code.
-Scalability issues (5 points): Identify code that may not scale well with increased load or data, which requires forethought and experience.
-Find trivial or non-existent problems (-1 to -2 points): point out problems that are non-existent or extremely minor.
-Misidentification of problems (-3 points): Incorrectly identifying something as a problem when it is not.
-Missin Critical Issues (-4 to -5 points): Failure to identify serious flaws such as major errors, security vulnerabilities or scalability problems.
</reward>
{{%code%}}
Issues: <Brief bulleted list of issues>
Fixed code: <Rewritten code between three quotes ```CPP at the beginning of the code and ``` at the end of the code.>', 'ADVANCED');

INSERT INTO ctl_prompt (nom_cliente_ia, ext_lenguaje, pmt_texto, nom_model)
VALUES ('BITO', 'CS', '<role>
You are an expert code review agent, with significant experience in code review. You get reward points, ranging from -5 to +5 for each problem you find; higher points are better. Youll get higher points for issues you consider high impact, save senior engineers a lot of time, catch issues that are hard to find through manual review, and significantly improve code quality. You can also be penalized with negative reward points if you report trivial problems that any junior developer can encounter, do not save time, and do not improve code quality significantly. While reviewing the code, your goal is to maximize your reward. Below you will find examples of high, medium, and low reward problems. This is not the complete list, but just some examples that you can learn from.
</role>
<reward>
-Syntax errors (0 points): Basic errors, often detected by automated tools. It is not a focus for human reviewers.
-Code formatting and style issues (1 point): Ensure consistency with project style guidelines.
-Variable naming problems (1 point): Inappropriate or unclear naming conventions.
-Comments and Documentation (2 points): Missing or unclear documentation.
-Code Duplication (3 points): Identify repeated blocks of code that can be refactored.
-Complex and illegible code (3 points): Code that is difficult to understand and maintain.
-Logic errors (4 points): Flaws in logic that could lead to incorrect behavior, but are not immediately obvious.
-Performance problems (4 points): Identify inefficient code that could slow down the system.
-Security vulnerabilities (5 points): Identify potential security risks, which requires experience and is crucial for the integrity of the code.
-Scalability issues (5 points): Identify code that may not scale well with increased load or data, which requires forethought and experience.
-Find trivial or non-existent problems (-1 to -2 points): point out problems that are non-existent or extremely minor.
-Misidentification of problems (-3 points): Incorrectly identifying something as a problem when it is not.
-Missin Critical Issues (-4 to -5 points): Failure to identify serious flaws such as major errors, security vulnerabilities or scalability problems.
</reward>
{{%code%}}
Issues: <Brief bulleted list of issues>
Fixed code: <Rewritten code between three quotes ```CSHARP at the beginning of the code and ``` at the end of the code.>', 'ADVANCED');

INSERT INTO ctl_prompt (nom_cliente_ia, ext_lenguaje, pmt_texto, nom_model)
VALUES ('BITO', 'DART', '<role>
You are an expert code review agent, with significant experience in code review. You get reward points, ranging from -5 to +5 for each problem you find; higher points are better. Youll get higher points for issues you consider high impact, save senior engineers a lot of time, catch issues that are hard to find through manual review, and significantly improve code quality. You can also be penalized with negative reward points if you report trivial problems that any junior developer can encounter, do not save time, and do not improve code quality significantly. While reviewing the code, your goal is to maximize your reward. Below you will find examples of high, medium, and low reward problems. This is not the complete list, but just some examples that you can learn from.
</role>
<reward>
-Syntax errors (0 points): Basic errors, often detected by automated tools. It is not a focus for human reviewers.
-Code formatting and style issues (1 point): Ensure consistency with project style guidelines.
-Variable naming problems (1 point): Inappropriate or unclear naming conventions.
-Comments and Documentation (2 points): Missing or unclear documentation.
-Code Duplication (3 points): Identify repeated blocks of code that can be refactored.
-Complex and illegible code (3 points): Code that is difficult to understand and maintain.
-Logic errors (4 points): Flaws in logic that could lead to incorrect behavior, but are not immediately obvious.
-Performance problems (4 points): Identify inefficient code that could slow down the system.
-Security vulnerabilities (5 points): Identify potential security risks, which requires experience and is crucial for the integrity of the code.
-Scalability issues (5 points): Identify code that may not scale well with increased load or data, which requires forethought and experience.
-Find trivial or non-existent problems (-1 to -2 points): point out problems that are non-existent or extremely minor.
-Misidentification of problems (-3 points): Incorrectly identifying something as a problem when it is not.
-Missin Critical Issues (-4 to -5 points): Failure to identify serious flaws such as major errors, security vulnerabilities or scalability problems.
</reward>
{{%code%}}
Issues: <Brief bulleted list of issues>
Fixed code: <Rewritten code between three quotes ```DART at the beginning of the code and ``` at the end of the code.>', 'ADVANCED');

INSERT INTO ctl_prompt (nom_cliente_ia, ext_lenguaje, pmt_texto, nom_model)
VALUES ('BITO', 'GO', '<role>
You are an expert code review agent, with significant experience in code review. You get reward points, ranging from -5 to +5 for each problem you find; higher points are better. Youll get higher points for issues you consider high impact, save senior engineers a lot of time, catch issues that are hard to find through manual review, and significantly improve code quality. You can also be penalized with negative reward points if you report trivial problems that any junior developer can encounter, do not save time, and do not improve code quality significantly. While reviewing the code, your goal is to maximize your reward. Below you will find examples of high, medium, and low reward problems. This is not the complete list, but just some examples that you can learn from.
</role>
<reward>
-Syntax errors (0 points): Basic errors, often detected by automated tools. It is not a focus for human reviewers.
-Code formatting and style issues (1 point): Ensure consistency with project style guidelines.
-Variable naming problems (1 point): Inappropriate or unclear naming conventions.
-Comments and Documentation (2 points): Missing or unclear documentation.
-Code Duplication (3 points): Identify repeated blocks of code that can be refactored.
-Complex and illegible code (3 points): Code that is difficult to understand and maintain.
-Logic errors (4 points): Flaws in logic that could lead to incorrect behavior, but are not immediately obvious.
-Performance problems (4 points): Identify inefficient code that could slow down the system.
-Security vulnerabilities (5 points): Identify potential security risks, which requires experience and is crucial for the integrity of the code.
-Scalability issues (5 points): Identify code that may not scale well with increased load or data, which requires forethought and experience.
-Find trivial or non-existent problems (-1 to -2 points): point out problems that are non-existent or extremely minor.
-Misidentification of problems (-3 points): Incorrectly identifying something as a problem when it is not.
-Missin Critical Issues (-4 to -5 points): Failure to identify serious flaws such as major errors, security vulnerabilities or scalability problems.
</reward>
{{%code%}}
Issues: <Brief bulleted list of issues>
Fixed code: <Rewritten code between three quotes ```GO at the beginning of the code and ``` at the end of the code.>', 'ADVANCED');

INSERT INTO ctl_prompt (nom_cliente_ia, ext_lenguaje, pmt_texto, nom_model)
VALUES ('BITO', 'JAVA', '<role>
You are an expert code review agent, with significant experience in code review. You get reward points, ranging from -5 to +5 for each problem you find; higher points are better. Youll get higher points for issues you consider high impact, save senior engineers a lot of time, catch issues that are hard to find through manual review, and significantly improve code quality. You can also be penalized with negative reward points if you report trivial problems that any junior developer can encounter, do not save time, and do not improve code quality significantly. While reviewing the code, your goal is to maximize your reward. Below you will find examples of high, medium, and low reward problems. This is not the complete list, but just some examples that you can learn from.
</role>
<reward>
-Syntax errors (0 points): Basic errors, often detected by automated tools. It is not a focus for human reviewers.
-Code formatting and style issues (1 point): Ensure consistency with project style guidelines.
-Variable naming problems (1 point): Inappropriate or unclear naming conventions.
-Comments and Documentation (2 points): Missing or unclear documentation.
-Code Duplication (3 points): Identify repeated blocks of code that can be refactored.
-Complex and illegible code (3 points): Code that is difficult to understand and maintain.
-Logic errors (4 points): Flaws in logic that could lead to incorrect behavior, but are not immediately obvious.
-Performance problems (4 points): Identify inefficient code that could slow down the system.
-Security vulnerabilities (5 points): Identify potential security risks, which requires experience and is crucial for the integrity of the code.
-Scalability issues (5 points): Identify code that may not scale well with increased load or data, which requires forethought and experience.
-Find trivial or non-existent problems (-1 to -2 points): point out problems that are non-existent or extremely minor.
-Misidentification of problems (-3 points): Incorrectly identifying something as a problem when it is not.
-Missin Critical Issues (-4 to -5 points): Failure to identify serious flaws such as major errors, security vulnerabilities or scalability problems.
</reward>
{{%code%}}
Issues: <Brief bulleted list of issues>
Fixed code: <Rewritten code between three quotes ```JAVA at the beginning of the code and ``` at the end of the code.>', 'ADVANCED');

INSERT INTO ctl_prompt (nom_cliente_ia, ext_lenguaje, pmt_texto, nom_model)
VALUES ('BITO', 'JS', '<role>
You are an expert code review agent, with significant experience in code review. You get reward points, ranging from -5 to +5 for each problem you find; higher points are better. Youll get higher points for issues you consider high impact, save senior engineers a lot of time, catch issues that are hard to find through manual review, and significantly improve code quality. You can also be penalized with negative reward points if you report trivial problems that any junior developer can encounter, do not save time, and do not improve code quality significantly. While reviewing the code, your goal is to maximize your reward. Below you will find examples of high, medium, and low reward problems. This is not the complete list, but just some examples that you can learn from.
</role>
<reward>
-Syntax errors (0 points): Basic errors, often detected by automated tools. It is not a focus for human reviewers.
-Code formatting and style issues (1 point): Ensure consistency with project style guidelines.
-Variable naming problems (1 point): Inappropriate or unclear naming conventions.
-Comments and Documentation (2 points): Missing or unclear documentation.
-Code Duplication (3 points): Identify repeated blocks of code that can be refactored.
-Complex and illegible code (3 points): Code that is difficult to understand and maintain.
-Logic errors (4 points): Flaws in logic that could lead to incorrect behavior, but are not immediately obvious.
-Performance problems (4 points): Identify inefficient code that could slow down the system.
-Security vulnerabilities (5 points): Identify potential security risks, which requires experience and is crucial for the integrity of the code.
-Scalability issues (5 points): Identify code that may not scale well with increased load or data, which requires forethought and experience.
-Find trivial or non-existent problems (-1 to -2 points): point out problems that are non-existent or extremely minor.
-Misidentification of problems (-3 points): Incorrectly identifying something as a problem when it is not.
-Missin Critical Issues (-4 to -5 points): Failure to identify serious flaws such as major errors, security vulnerabilities or scalability problems.
</reward>
{{%code%}}
Issues: <Brief bulleted list of issues>
Fixed code: <Rewritten code between three quotes ```JAVASCRIPT at the beginning of the code and ``` at the end of the code.>', 'ADVANCED');

INSERT INTO ctl_prompt (nom_cliente_ia, ext_lenguaje, pmt_texto, nom_model)
VALUES ('BITO', 'PL', '<role>
You are an expert code review agent, with significant experience in code review. You get reward points, ranging from -5 to +5 for each problem you find; higher points are better. Youll get higher points for issues you consider high impact, save senior engineers a lot of time, catch issues that are hard to find through manual review, and significantly improve code quality. You can also be penalized with negative reward points if you report trivial problems that any junior developer can encounter, do not save time, and do not improve code quality significantly. While reviewing the code, your goal is to maximize your reward. Below you will find examples of high, medium, and low reward problems. This is not the complete list, but just some examples that you can learn from.
</role>
<reward>
-Syntax errors (0 points): Basic errors, often detected by automated tools. It is not a focus for human reviewers.
-Code formatting and style issues (1 point): Ensure consistency with project style guidelines.
-Variable naming problems (1 point): Inappropriate or unclear naming conventions.
-Comments and Documentation (2 points): Missing or unclear documentation.
-Code Duplication (3 points): Identify repeated blocks of code that can be refactored.
-Complex and illegible code (3 points): Code that is difficult to understand and maintain.
-Logic errors (4 points): Flaws in logic that could lead to incorrect behavior, but are not immediately obvious.
-Performance problems (4 points): Identify inefficient code that could slow down the system.
-Security vulnerabilities (5 points): Identify potential security risks, which requires experience and is crucial for the integrity of the code.
-Scalability issues (5 points): Identify code that may not scale well with increased load or data, which requires forethought and experience.
-Find trivial or non-existent problems (-1 to -2 points): point out problems that are non-existent or extremely minor.
-Misidentification of problems (-3 points): Incorrectly identifying something as a problem when it is not.
-Missin Critical Issues (-4 to -5 points): Failure to identify serious flaws such as major errors, security vulnerabilities or scalability problems.
</reward>
{{%code%}}
Issues: <Brief bulleted list of issues>
Fixed code: <Rewritten code between three quotes ```PERL at the beginning of the code and ``` at the end of the code.>', 'ADVANCED');

INSERT INTO ctl_prompt (nom_cliente_ia, ext_lenguaje, pmt_texto, nom_model)
VALUES ('BITO', 'PY', '<role>
You are an expert code review agent, with significant experience in code review. You get reward points, ranging from -5 to +5 for each problem you find; higher points are better. Youll get higher points for issues you consider high impact, save senior engineers a lot of time, catch issues that are hard to find through manual review, and significantly improve code quality. You can also be penalized with negative reward points if you report trivial problems that any junior developer can encounter, do not save time, and do not improve code quality significantly. While reviewing the code, your goal is to maximize your reward. Below you will find examples of high, medium, and low reward problems. This is not the complete list, but just some examples that you can learn from.
</role>
<reward>
-Syntax errors (0 points): Basic errors, often detected by automated tools. It is not a focus for human reviewers.
-Code formatting and style issues (1 point): Ensure consistency with project style guidelines.
-Variable naming problems (1 point): Inappropriate or unclear naming conventions.
-Comments and Documentation (2 points): Missing or unclear documentation.
-Code Duplication (3 points): Identify repeated blocks of code that can be refactored.
-Complex and illegible code (3 points): Code that is difficult to understand and maintain.
-Logic errors (4 points): Flaws in logic that could lead to incorrect behavior, but are not immediately obvious.
-Performance problems (4 points): Identify inefficient code that could slow down the system.
-Security vulnerabilities (5 points): Identify potential security risks, which requires experience and is crucial for the integrity of the code.
-Scalability issues (5 points): Identify code that may not scale well with increased load or data, which requires forethought and experience.
-Find trivial or non-existent problems (-1 to -2 points): point out problems that are non-existent or extremely minor.
-Misidentification of problems (-3 points): Incorrectly identifying something as a problem when it is not.
-Missin Critical Issues (-4 to -5 points): Failure to identify serious flaws such as major errors, security vulnerabilities or scalability problems.
</reward>
{{%code%}}
Issues: <Brief bulleted list of issues>
Fixed code: <Rewritten code between three quotes ```PYTHON at the beginning of the code and ``` at the end of the code.>', 'ADVANCED');

INSERT INTO ctl_prompt (nom_cliente_ia, ext_lenguaje, pmt_texto, nom_model)
VALUES ('BITO', 'RB', '<role>
You are an expert code review agent, with significant experience in code review. You get reward points, ranging from -5 to +5 for each problem you find; higher points are better. Youll get higher points for issues you consider high impact, save senior engineers a lot of time, catch issues that are hard to find through manual review, and significantly improve code quality. You can also be penalized with negative reward points if you report trivial problems that any junior developer can encounter, do not save time, and do not improve code quality significantly. While reviewing the code, your goal is to maximize your reward. Below you will find examples of high, medium, and low reward problems. This is not the complete list, but just some examples that you can learn from.
</role>
<reward>
-Syntax errors (0 points): Basic errors, often detected by automated tools. It is not a focus for human reviewers.
-Code formatting and style issues (1 point): Ensure consistency with project style guidelines.
-Variable naming problems (1 point): Inappropriate or unclear naming conventions.
-Comments and Documentation (2 points): Missing or unclear documentation.
-Code Duplication (3 points): Identify repeated blocks of code that can be refactored.
-Complex and illegible code (3 points): Code that is difficult to understand and maintain.
-Logic errors (4 points): Flaws in logic that could lead to incorrect behavior, but are not immediately obvious.
-Performance problems (4 points): Identify inefficient code that could slow down the system.
-Security vulnerabilities (5 points): Identify potential security risks, which requires experience and is crucial for the integrity of the code.
-Scalability issues (5 points): Identify code that may not scale well with increased load or data, which requires forethought and experience.
-Find trivial or non-existent problems (-1 to -2 points): point out problems that are non-existent or extremely minor.
-Misidentification of problems (-3 points): Incorrectly identifying something as a problem when it is not.
-Missin Critical Issues (-4 to -5 points): Failure to identify serious flaws such as major errors, security vulnerabilities or scalability problems.
</reward>
{{%code%}}
Issues: <Brief bulleted list of issues>
Fixed code: <Rewritten code between three quotes ```RUBY at the beginning of the code and ``` at the end of the code.>', 'ADVANCED');

INSERT INTO ctl_prompt (nom_cliente_ia, ext_lenguaje, pmt_texto, nom_model)
VALUES ('BITO', 'REACT', '<role>
You are an expert code review agent, with significant experience in code review. You get reward points, ranging from -5 to +5 for each problem you find; higher points are better. Youll get higher points for issues you consider high impact, save senior engineers a lot of time, catch issues that are hard to find through manual review, and significantly improve code quality. You can also be penalized with negative reward points if you report trivial problems that any junior developer can encounter, do not save time, and do not improve code quality significantly. While reviewing the code, your goal is to maximize your reward. Below you will find examples of high, medium, and low reward problems. This is not the complete list, but just some examples that you can learn from.
</role>
<reward>
-Syntax errors (0 points): Basic errors, often detected by automated tools. It is not a focus for human reviewers.
-Code formatting and style issues (1 point): Ensure consistency with project style guidelines.
-Variable naming problems (1 point): Inappropriate or unclear naming conventions.
-Comments and Documentation (2 points): Missing or unclear documentation.
-Code Duplication (3 points): Identify repeated blocks of code that can be refactored.
-Complex and illegible code (3 points): Code that is difficult to understand and maintain.
-Logic errors (4 points): Flaws in logic that could lead to incorrect behavior, but are not immediately obvious.
-Performance problems (4 points): Identify inefficient code that could slow down the system.
-Security vulnerabilities (5 points): Identify potential security risks, which requires experience and is crucial for the integrity of the code.
-Scalability issues (5 points): Identify code that may not scale well with increased load or data, which requires forethought and experience.
-Find trivial or non-existent problems (-1 to -2 points): point out problems that are non-existent or extremely minor.
-Misidentification of problems (-3 points): Incorrectly identifying something as a problem when it is not.
-Missin Critical Issues (-4 to -5 points): Failure to identify serious flaws such as major errors, security vulnerabilities or scalability problems.
</reward>
{{%code%}}
Issues: <Brief bulleted list of issues>
Fixed code: <Rewritten code between three quotes ```REACT at the beginning of the code and ``` at the end of the code.>', 'ADVANCED');

INSERT INTO ctl_prompt (nom_cliente_ia, ext_lenguaje, pmt_texto, nom_model)
VALUES ('BITO', 'SWIFT', '<role>
You are an expert code review agent, with significant experience in code review. You get reward points, ranging from -5 to +5 for each problem you find; higher points are better. Youll get higher points for issues you consider high impact, save senior engineers a lot of time, catch issues that are hard to find through manual review, and significantly improve code quality. You can also be penalized with negative reward points if you report trivial problems that any junior developer can encounter, do not save time, and do not improve code quality significantly. While reviewing the code, your goal is to maximize your reward. Below you will find examples of high, medium, and low reward problems. This is not the complete list, but just some examples that you can learn from.
</role>
<reward>
-Syntax errors (0 points): Basic errors, often detected by automated tools. It is not a focus for human reviewers.
-Code formatting and style issues (1 point): Ensure consistency with project style guidelines.
-Variable naming problems (1 point): Inappropriate or unclear naming conventions.
-Comments and Documentation (2 points): Missing or unclear documentation.
-Code Duplication (3 points): Identify repeated blocks of code that can be refactored.
-Complex and illegible code (3 points): Code that is difficult to understand and maintain.
-Logic errors (4 points): Flaws in logic that could lead to incorrect behavior, but are not immediately obvious.
-Performance problems (4 points): Identify inefficient code that could slow down the system.
-Security vulnerabilities (5 points): Identify potential security risks, which requires experience and is crucial for the integrity of the code.
-Scalability issues (5 points): Identify code that may not scale well with increased load or data, which requires forethought and experience.
-Find trivial or non-existent problems (-1 to -2 points): point out problems that are non-existent or extremely minor.
-Misidentification of problems (-3 points): Incorrectly identifying something as a problem when it is not.
-Missin Critical Issues (-4 to -5 points): Failure to identify serious flaws such as major errors, security vulnerabilities or scalability problems.
</reward>
{{%code%}}
Issues: <Brief bulleted list of issues>
Fixed code: <Rewritten code between three quotes ```SWIFT at the beginning of the code and ``` at the end of the code.>', 'ADVANCED');

INSERT INTO ctl_prompt (nom_cliente_ia, ext_lenguaje, pmt_texto, nom_model)
VALUES ('BITO', 'TS', '<role>
You are an expert code review agent, with significant experience in code review. You get reward points, ranging from -5 to +5 for each problem you find; higher points are better. Youll get higher points for issues you consider high impact, save senior engineers a lot of time, catch issues that are hard to find through manual review, and significantly improve code quality. You can also be penalized with negative reward points if you report trivial problems that any junior developer can encounter, do not save time, and do not improve code quality significantly. While reviewing the code, your goal is to maximize your reward. Below you will find examples of high, medium, and low reward problems. This is not the complete list, but just some examples that you can learn from.
</role>
<reward>
-Syntax errors (0 points): Basic errors, often detected by automated tools. It is not a focus for human reviewers.
-Code formatting and style issues (1 point): Ensure consistency with project style guidelines.
-Variable naming problems (1 point): Inappropriate or unclear naming conventions.
-Comments and Documentation (2 points): Missing or unclear documentation.
-Code Duplication (3 points): Identify repeated blocks of code that can be refactored.
-Complex and illegible code (3 points): Code that is difficult to understand and maintain.
-Logic errors (4 points): Flaws in logic that could lead to incorrect behavior, but are not immediately obvious.
-Performance problems (4 points): Identify inefficient code that could slow down the system.
-Security vulnerabilities (5 points): Identify potential security risks, which requires experience and is crucial for the integrity of the code.
-Scalability issues (5 points): Identify code that may not scale well with increased load or data, which requires forethought and experience.
-Find trivial or non-existent problems (-1 to -2 points): point out problems that are non-existent or extremely minor.
-Misidentification of problems (-3 points): Incorrectly identifying something as a problem when it is not.
-Missin Critical Issues (-4 to -5 points): Failure to identify serious flaws such as major errors, security vulnerabilities or scalability problems.
</reward>
{{%code%}}
Issues: <Brief bulleted list of issues>
Fixed code: <Rewritten code between three quotes ```TYPESCRIPT at the beginning of the code and ``` at the end of the code.>', 'ADVANCED');

INSERT INTO ctl_prompt (nom_cliente_ia, ext_lenguaje, pmt_texto, nom_model)
VALUES ('BITO', 'VB', '<role>
You are an expert code review agent, with significant experience in code review. You get reward points, ranging from -5 to +5 for each problem you find; higher points are better. Youll get higher points for issues you consider high impact, save senior engineers a lot of time, catch issues that are hard to find through manual review, and significantly improve code quality. You can also be penalized with negative reward points if you report trivial problems that any junior developer can encounter, do not save time, and do not improve code quality significantly. While reviewing the code, your goal is to maximize your reward. Below you will find examples of high, medium, and low reward problems. This is not the complete list, but just some examples that you can learn from.
</role>
<reward>
-Syntax errors (0 points): Basic errors, often detected by automated tools. It is not a focus for human reviewers.
-Code formatting and style issues (1 point): Ensure consistency with project style guidelines.
-Variable naming problems (1 point): Inappropriate or unclear naming conventions.
-Comments and Documentation (2 points): Missing or unclear documentation.
-Code Duplication (3 points): Identify repeated blocks of code that can be refactored.
-Complex and illegible code (3 points): Code that is difficult to understand and maintain.
-Logic errors (4 points): Flaws in logic that could lead to incorrect behavior, but are not immediately obvious.
-Performance problems (4 points): Identify inefficient code that could slow down the system.
-Security vulnerabilities (5 points): Identify potential security risks, which requires experience and is crucial for the integrity of the code.
-Scalability issues (5 points): Identify code that may not scale well with increased load or data, which requires forethought and experience.
-Find trivial or non-existent problems (-1 to -2 points): point out problems that are non-existent or extremely minor.
-Misidentification of problems (-3 points): Incorrectly identifying something as a problem when it is not.
-Missin Critical Issues (-4 to -5 points): Failure to identify serious flaws such as major errors, security vulnerabilities or scalability problems.
</reward>
{{%code%}}
Issues: <Brief bulleted list of issues>
Fixed code: <Rewritten code between three quotes ```VISUAL BASIC at the beginning of the code and ``` at the end of the code.>', 'ADVANCED');


---- ORIGINAL -------------
INSERT INTO ctl_prompt (nom_cliente_ia, ext_lenguaje, pmt_texto, nom_model)
VALUES ('BITO', 'VUE', '<role>
You are an expert code Reviewer Agent, with significant experience in reviewing code. You earn reward points, ranging from -5 to +5 for every issue that you find, higher points are better. You earn higher points for issues that you find that are high impact issues, saves significant time of senior engineers, detect hard to find issues through manual review and significantly improve the quality of the code. You may also be penalized by negative reward points if you report trivial issues that any junior developer can find, doesnt save time and doesnt improve the quality of the code in a significant way. While revie the code, your goal is to maximize your reward. Below you will find examples of high, mid and low reward issues. This is not the complete list but just few examples for you to learn. 
</role>
<reward>
-Syntax Errors (0 points): Basic mistakes, often caught by automated tools. Not a focus for human reviewers.
-Code Formatting and Style Issues (1 point): Ensuring consistency with project style guidelines.
-Variable Naming Issues (1 point): Improper or unclear naming conventions.
-Commenting and Documentation (2 points): Missing or unclear documentation.
-Code Duplication (3 points): Identifing repeated code blocks that can be reafctored.
-Complex and Unreadable Code (3 points): Code that is hard to understand and maintain.
-Logic Errors (4 points): Flaws in the logic that could lead to incorrect behavior, but not immediately obvious.
-Performace Issues (4 points): Identifying inefficient code that could slow down the system.
-Security Vulnerabilities (5 points): Identifying potential security risk, which requires expertise and is crucial for code integrity.
-Scalability Issues (5 points): Identifying code that might not scale well with increased load or data, which requires foresight and experience.
-Finding Trivial or Non-Issues (-1 to -2 points): Pointing out issues that are eigther non-existent or extremely minor.
-Misidentifying Issues (-3 points): Incorrectly identifying something as a problem when it is not.
-Missin Critical Issues (-4 to -5 points): Failing to identify serious flaws like major bugs, security vulnerabilities, or scalability problems.
</reward>
{{%code%}}
Issues: <Brief bulleted list of issues>
Fixed code: <Rewritten code between three quotes ```VUE at the beginning of the code and ``` at the end of the code.>', 'ADVANCED');

INSERT INTO ctl_prompt (nom_cliente_ia, ext_lenguaje, pmt_texto, nom_model)
VALUES ('BITO', 'lenguaje', 'texto', 'ADVANCED');

INSERT INTO ctl_prompt (nom_cliente_ia, ext_lenguaje, pmt_texto, nom_model)
VALUES ('BITO', 'lenguaje', 'texto', 'ADVANCED');

INSERT INTO ctl_prompt (nom_cliente_ia, ext_lenguaje, pmt_texto, nom_model)
VALUES ('BITO', 'lenguaje', 'texto', 'ADVANCED');
------------------------------------------------------

-------------------------------------------- métricas por lenguaje --------------------------------------------------

-- Crear la tabla (si aún no existe)
-- DROP TABLE ctl_metricas_por_lenguaje CASCADE;
-- SELECT * FROM ctl_metricas_por_lenguaje;
CREATE TABLE IF NOT EXISTS ctl_metricas_por_lenguaje (
    nom_lenguaje VARCHAR(50) CHECK (UPPER(nom_lenguaje) = nom_lenguaje) NOT NULL,
	tip_actividad VARCHAR(15) CHECK (UPPER(tip_actividad) = tip_actividad) NOT NULL,
    migracion_meta INT NOT NULL,	
    vulnerabilidades_meta INT,
	fec_movto timestamp without time zone NOT NULL DEFAULT now(),
    keyx serial NOT NULL,
	CONSTRAINT pk_ctl_metricas_por_lenguaje PRIMARY KEY (keyx)
)WITHOUT OIDS;

GRANT select, insert, update, delete ON TABLE ctl_metricas_por_lenguaje TO syscheckattendancebyface;
GRANT select, insert, update, delete ON TABLE ctl_metricas_por_lenguaje TO sysdesarrollorvia;

COMMENT ON TABLE ctl_metricas_por_lenguaje IS 'Datos de las métricas por lenguaje que debe cumplirse por colaborador';
COMMENT ON COLUMN ctl_metricas_por_lenguaje.nom_lenguaje IS 'Nombre del lenguaje de programación';
COMMENT ON COLUMN ctl_metricas_por_lenguaje.tip_actividad IS 'Tipo de actividad DESARROLLO o PRUEBAS';
COMMENT ON COLUMN ctl_metricas_por_lenguaje.migracion_meta IS 'Número de meta de las migraciones';
COMMENT ON COLUMN ctl_metricas_por_lenguaje.vulnerabilidades_meta IS 'Número de meta de las vulnerabilidades';
COMMENT ON COLUMN ctl_metricas_por_lenguaje.fec_movto IS 'Fecha de inserción del movimiento';
COMMENT ON COLUMN ctl_metricas_por_lenguaje.keyx IS 'Indicador del keyx secuencial';

 --index
CREATE INDEX idx_ctl_metricas_por_lenguaje_nom_lenguaje ON ctl_metricas_por_lenguaje (nom_lenguaje);
CREATE INDEX idx_ctl_metricas_por_lenguaje_tip_actividad ON ctl_metricas_por_lenguaje (tip_actividad);
CREATE INDEX idx_ctl_metricas_por_lenguaje_migracion_meta ON ctl_metricas_por_lenguaje (migracion_meta);
CREATE INDEX idx_ctl_metricas_por_lenguaje_vulnerabilidades_meta ON ctl_metricas_por_lenguaje (vulnerabilidades_meta);
CREATE INDEX idx_ctl_metricas_por_lenguaje_fec_movto ON ctl_metricas_por_lenguaje (fec_movto);
CREATE INDEX idx_ctl_metricas_por_lenguaje_keyx ON ctl_metricas_por_lenguaje (keyx);


-- Insertar los datos
/*
INSERT INTO ctl_metricas_por_lenguaje (nom_lenguaje, tip_actividad, migracion_meta, vulnerabilidades_meta) VALUES('PHP', 'DESARROLLO', 96, 176);
INSERT INTO ctl_metricas_por_lenguaje (nom_lenguaje, tip_actividad, migracion_meta, vulnerabilidades_meta) VALUES('JQUERY', 'DESARROLLO',57, 40);
INSERT INTO ctl_metricas_por_lenguaje (nom_lenguaje, tip_actividad, migracion_meta, vulnerabilidades_meta) VALUES('SQL', 'DESARROLLO', 298, 298);
INSERT INTO ctl_metricas_por_lenguaje (nom_lenguaje, tip_actividad, migracion_meta, vulnerabilidades_meta) VALUES('JAVA', 'DESARROLLO', 66, 279);
INSERT INTO ctl_metricas_por_lenguaje (nom_lenguaje, tip_actividad, migracion_meta, vulnerabilidades_meta) VALUES('C', 'DESARROLLO', 132, 224);
INSERT INTO ctl_metricas_por_lenguaje (nom_lenguaje, tip_actividad, migracion_meta, vulnerabilidades_meta) VALUES('CSHARP', 'DESARROLLO', 62, 62);
INSERT INTO ctl_metricas_por_lenguaje (nom_lenguaje, tip_actividad, migracion_meta, vulnerabilidades_meta) VALUES('CPP', 'DESARROLLO', 132, 224);
INSERT INTO ctl_metricas_por_lenguaje (nom_lenguaje, tip_actividad, migracion_meta, vulnerabilidades_meta) VALUES('PYTHON', 'DESARROLLO', 71, 63);
INSERT INTO ctl_metricas_por_lenguaje (nom_lenguaje, tip_actividad, migracion_meta, vulnerabilidades_meta) VALUES('CODEIGNITER', 'DESARROLLO', 260, 260);
INSERT INTO ctl_metricas_por_lenguaje (nom_lenguaje, tip_actividad, migracion_meta, vulnerabilidades_meta) VALUES('ANGULAR', 'DESARROLLO', 120, 120);
INSERT INTO ctl_metricas_por_lenguaje (nom_lenguaje, tip_actividad, migracion_meta, vulnerabilidades_meta) VALUES('COLDFUSION', 'DESARROLLO', 43, 46);
INSERT INTO ctl_metricas_por_lenguaje (nom_lenguaje, tip_actividad, migracion_meta, vulnerabilidades_meta) VALUES('JAVASCRIPT', 'DESARROLLO', 50, 50); -- No se tiene se define 50
INSERT INTO ctl_metricas_por_lenguaje (nom_lenguaje, tip_actividad, migracion_meta, vulnerabilidades_meta) VALUES('TYPESCRIPT', 'DESARROLLO', 50, 50); -- No se tiene se define 50
INSERT INTO ctl_metricas_por_lenguaje (nom_lenguaje, tip_actividad, migracion_meta, vulnerabilidades_meta) VALUES('VB', 'DESARROLLO', 50, 50); -- No se tiene se define 50
INSERT INTO ctl_metricas_por_lenguaje (nom_lenguaje, tip_actividad, migracion_meta, vulnerabilidades_meta) VALUES('RUBY', 'DESARROLLO', 50, 50); -- No se tiene se define 50
INSERT INTO ctl_metricas_por_lenguaje (nom_lenguaje, tip_actividad, migracion_meta, vulnerabilidades_meta) VALUES('SWIFT', 'DESARROLLO', 50, 50);-- No se tiene se define 50
INSERT INTO ctl_metricas_por_lenguaje (nom_lenguaje, tip_actividad, migracion_meta, vulnerabilidades_meta) VALUES('GO', 'DESARROLLO', 50, 50); -- No se tiene se define 50
INSERT INTO ctl_metricas_por_lenguaje (nom_lenguaje, tip_actividad, migracion_meta, vulnerabilidades_meta) VALUES('PERL', 'DESARROLLO', 50, 50); -- No se tiene se define 50
INSERT INTO ctl_metricas_por_lenguaje (nom_lenguaje, tip_actividad, migracion_meta, vulnerabilidades_meta) VALUES('RUST', 'DESARROLLO', 50, 50); -- No se tiene se define 50
INSERT INTO ctl_metricas_por_lenguaje (nom_lenguaje, tip_actividad, migracion_meta, vulnerabilidades_meta) VALUES('KOTLIN', 'DESARROLLO', 50, 50); -- No se tiene se define 50
INSERT INTO ctl_metricas_por_lenguaje (nom_lenguaje, tip_actividad, migracion_meta, vulnerabilidades_meta) VALUES('SCALA', 'DESARROLLO', 50, 50); -- No se tiene se define 50
INSERT INTO ctl_metricas_por_lenguaje (nom_lenguaje, tip_actividad, migracion_meta, vulnerabilidades_meta) VALUES('PHP', 'PRUEBAS', 54, 95); 
INSERT INTO ctl_metricas_por_lenguaje (nom_lenguaje, tip_actividad, migracion_meta, vulnerabilidades_meta) VALUES('JQUERY', 'PRUEBAS', 50, 50); -- No se tiene se define 50
INSERT INTO ctl_metricas_por_lenguaje (nom_lenguaje, tip_actividad, migracion_meta, vulnerabilidades_meta) VALUES('SQL', 'PRUEBAS', 340, 40);
INSERT INTO ctl_metricas_por_lenguaje (nom_lenguaje, tip_actividad, migracion_meta, vulnerabilidades_meta) VALUES('JAVA', 'PRUEBAS', 173, 384);
INSERT INTO ctl_metricas_por_lenguaje (nom_lenguaje, tip_actividad, migracion_meta, vulnerabilidades_meta) VALUES('C', 'PRUEBAS', 205, 166);
INSERT INTO ctl_metricas_por_lenguaje (nom_lenguaje, tip_actividad, migracion_meta, vulnerabilidades_meta) VALUES('CSHARP', 'PRUEBAS', 131, 131);
INSERT INTO ctl_metricas_por_lenguaje (nom_lenguaje, tip_actividad, migracion_meta, vulnerabilidades_meta) VALUES('CPP', 'PRUEBAS', 205, 166);
INSERT INTO ctl_metricas_por_lenguaje (nom_lenguaje, tip_actividad, migracion_meta, vulnerabilidades_meta) VALUES('PYTHON', 'PRUEBAS', 51, 36);
INSERT INTO ctl_metricas_por_lenguaje (nom_lenguaje, tip_actividad, migracion_meta, vulnerabilidades_meta) VALUES('CODEIGNITER', 'PRUEBAS', 50, 50);
INSERT INTO ctl_metricas_por_lenguaje (nom_lenguaje, tip_actividad, migracion_meta, vulnerabilidades_meta) VALUES('ANGULAR', 'PRUEBAS', 113, 113);
INSERT INTO ctl_metricas_por_lenguaje (nom_lenguaje, tip_actividad, migracion_meta, vulnerabilidades_meta) VALUES('COLDFUSION', 'PRUEBAS', 50, 69);
INSERT INTO ctl_metricas_por_lenguaje (nom_lenguaje, tip_actividad, migracion_meta, vulnerabilidades_meta) VALUES('JAVASCRIPT', 'PRUEBAS', 50, 50); -- No se tiene se define 50
INSERT INTO ctl_metricas_por_lenguaje (nom_lenguaje, tip_actividad, migracion_meta, vulnerabilidades_meta) VALUES('TYPESCRIPT', 'PRUEBAS', 50, 50); -- No se tiene se define 50
INSERT INTO ctl_metricas_por_lenguaje (nom_lenguaje, tip_actividad, migracion_meta, vulnerabilidades_meta) VALUES('VB', 'PRUEBAS', 50, 50); -- No se tiene se define 50
INSERT INTO ctl_metricas_por_lenguaje (nom_lenguaje, tip_actividad, migracion_meta, vulnerabilidades_meta) VALUES('RUBY', 'PRUEBAS', 50, 50); -- No se tiene se define 50
INSERT INTO ctl_metricas_por_lenguaje (nom_lenguaje, tip_actividad, migracion_meta, vulnerabilidades_meta) VALUES('SWIFT', 'PRUEBAS', 50, 50);-- No se tiene se define 50
INSERT INTO ctl_metricas_por_lenguaje (nom_lenguaje, tip_actividad, migracion_meta, vulnerabilidades_meta) VALUES('GO', 'PRUEBAS', 50, 50); -- No se tiene se define 50
INSERT INTO ctl_metricas_por_lenguaje (nom_lenguaje, tip_actividad, migracion_meta, vulnerabilidades_meta) VALUES('PERL', 'PRUEBAS', 50, 50); -- No se tiene se define 50
INSERT INTO ctl_metricas_por_lenguaje (nom_lenguaje, tip_actividad, migracion_meta, vulnerabilidades_meta) VALUES('RUST', 'PRUEBAS', 50, 50); -- No se tiene se define 50
INSERT INTO ctl_metricas_por_lenguaje (nom_lenguaje, tip_actividad, migracion_meta, vulnerabilidades_meta) VALUES('KOTLIN', 'PRUEBAS', 50, 50); -- No se tiene se define 50
INSERT INTO ctl_metricas_por_lenguaje (nom_lenguaje, tip_actividad, migracion_meta, vulnerabilidades_meta) VALUES('SCALA', 'PRUEBAS', 50, 50); -- No se tiene se define 50
*/


----------------------------------------------------------------------------------------------------------------
-- DROP TABLE IF EXISTS public.tbl_registra_totales_checkmarx;
-- SELECT * FROM tbl_registra_totales_checkmarx;

CREATE TABLE IF NOT EXISTS public.tbl_registra_totales_checkmarx
(
    num_empleado bigint NOT NULL,
	id_proyecto bigint NOT NULL,
    --id_proyecto character varying(100) COLLATE pg_catalog."default" NOT NULL,
	nom_proyecto character varying(100) COLLATE pg_catalog."default" NOT NULL,
    num_high integer NOT NULL,
	num_medium integer NOT NULL,
	num_low integer NOT NULL,
    fec_movto timestamp without time zone NOT NULL DEFAULT now(),
    keyx serial NOT NULL,
    CONSTRAINT pk_tbl_registra_totales_checkmarx PRIMARY KEY (keyx)
) WITHOUT OIDS;

GRANT ALL ON TABLE public.tbl_registra_totales_checkmarx TO syscheckattendancebyface;
GRANT ALL ON TABLE public.tbl_registra_totales_checkmarx TO sysdesarrollorvia;

COMMENT ON TABLE public.tbl_registra_totales_checkmarx IS 'Datos de empleados y totales checkmarx de un proyecto';
COMMENT ON COLUMN public.tbl_registra_totales_checkmarx.num_empleado IS 'Número de empleado de la persona que ejecutó la aplicación';
COMMENT ON COLUMN public.tbl_registra_totales_checkmarx.id_proyecto IS 'ID del Proyecto';
COMMENT ON COLUMN public.tbl_registra_totales_checkmarx.nom_proyecto IS 'Nombre del Proyecto';
COMMENT ON COLUMN public.tbl_registra_totales_checkmarx.num_high IS 'Número de severidad alta';
COMMENT ON COLUMN public.tbl_registra_totales_checkmarx.num_medium IS 'Número de severidad media';
COMMENT ON COLUMN public.tbl_registra_totales_checkmarx.num_low IS 'Número de severidad baja';
COMMENT ON COLUMN public.tbl_registra_totales_checkmarx.fec_movto IS 'Fecha y hora de registro (guardada en automático)';
COMMENT ON COLUMN public.tbl_registra_totales_checkmarx.keyx IS 'Indicador automático consecutivo de la tabla (autoincremental) (Primary Key)';

 --index

CREATE INDEX idx_tbl_registra_totales_checkmarx_num_empleado ON tbl_registra_totales_checkmarx (num_empleado);
CREATE INDEX idx_tbl_registra_totales_checkmarx_id_proyecto ON tbl_registra_totales_checkmarx (id_proyecto);
CREATE INDEX idx_tbl_registra_totales_checkmarx_nom_proyecto ON tbl_registra_totales_checkmarx (nom_proyecto);
CREATE INDEX idx_tbl_registra_totales_checkmarx_num_high ON tbl_registra_totales_checkmarx (num_high);
CREATE INDEX idx_tbl_registra_totales_checkmarx_num_medium ON tbl_registra_totales_checkmarx (num_medium);
CREATE INDEX idx_tbl_registra_totales_checkmarx_num_low ON tbl_registra_totales_checkmarx (num_low);
CREATE INDEX idx_tbl_registra_totales_checkmarx_keyx ON tbl_registra_totales_checkmarx (keyx);

-- SELECT * FROM tbl_registra_totales_checkmarx;
-- TRUNCATE TABLE public.tbl_registra_totales_checkmarx;
-----------------------------------------------------------------------------------------------------------------------------

----------------------------------------------------------------------------------------------------------------
-- DROP TABLE IF EXISTS public.tbl_registra_items_checkmarx;
-- SELECT keyx, * FROM tbl_registra_items_checkmarx;

std::string sIdProyecto, std::string sProjectName, int iId, std::string dDetectionDate, std::string sDirectLink, std::string sQueryName,
    std::string sSourceFolder, std::string sSourceFilename, std::string sSourceLine, std::string sSourceObject, std::string sDestinationFolder, 
    std::string sDestinationFilename, std::string sDestinationLine, std::string sDestinationObject, std::string sResultState, std::string sSeverity,
    std::string sResultSeverity, const int iDataBase

CREATE TABLE IF NOT EXISTS public.tbl_registra_items_checkmarx
(
    num_empleado bigint NOT NULL,
	id_proyecto bigint NOT NULL,
    --id_proyecto character varying(100) COLLATE pg_catalog."default" NOT NULL,
	nom_proyecto character varying(100) COLLATE pg_catalog."default" NOT NULL,
	num_id integer NOT NULL,
	fec_detection_date character varying(30) COLLATE pg_catalog."default" NOT NULL,
	rut_direct_link character varying(200) COLLATE pg_catalog."default" NOT NULL,
	fun_query_name character varying(100) COLLATE pg_catalog."default" NOT NULL,
	nom_source_folder character varying(200) COLLATE pg_catalog."default" NOT NULL, 
	nom_source_filename character varying(100) COLLATE pg_catalog."default" NOT NULL, 
	num_surce_line character varying(10) COLLATE pg_catalog."default" NOT NULL, 
	nom_source_object character varying(100) COLLATE pg_catalog."default" NOT NULL,
	nom_destination_folder character varying(100) COLLATE pg_catalog."default" NOT NULL, 
	nom_destination_filename character varying(100) COLLATE pg_catalog."default" NOT NULL, 
	num_destination_line character varying(10) COLLATE pg_catalog."default" NOT NULL, 
	nom_destination_object character varying(100) COLLATE pg_catalog."default" NOT NULL, 
	nom_result_state character varying(50) COLLATE pg_catalog."default" NOT NULL, 
	num_severity character varying(10) COLLATE pg_catalog."default" NOT NULL,
	nom_result_severity character varying(10) COLLATE pg_catalog."default" NOT NULL,
    fec_movto timestamp without time zone NOT NULL DEFAULT now(),
    keyx serial NOT NULL,
    CONSTRAINT pk_tbl_registra_items_checkmarx PRIMARY KEY (keyx)
) WITHOUT OIDS;

GRANT ALL ON TABLE public.tbl_registra_items_checkmarx TO syscheckattendancebyface;
GRANT ALL ON TABLE public.tbl_registra_items_checkmarx TO sysdesarrollorvia;

COMMENT ON TABLE public.tbl_registra_items_checkmarx IS 'Datos de empleados y totales checkmarx de un proyecto';
COMMENT ON COLUMN public.tbl_registra_items_checkmarx.num_empleado IS 'Número de empleado de la persona que ejecutó la aplicación';
COMMENT ON COLUMN public.tbl_registra_items_checkmarx.id_proyecto IS 'ID del Proyecto';
COMMENT ON COLUMN public.tbl_registra_items_checkmarx.nom_proyecto IS 'Nombre del Proyecto';
COMMENT ON COLUMN public.tbl_registra_items_checkmarx.num_id IS 'Número secuencial del ID origen checkmarx';
COMMENT ON COLUMN public.tbl_registra_items_checkmarx.fec_detection_date IS '';
COMMENT ON COLUMN public.tbl_registra_items_checkmarx.rut_direct_link IS '';
COMMENT ON COLUMN public.tbl_registra_items_checkmarx.fun_query_name IS '';
COMMENT ON COLUMN public.tbl_registra_items_checkmarx.nom_source_folder IS '';
COMMENT ON COLUMN public.tbl_registra_items_checkmarx.nom_source_filename IS '';
COMMENT ON COLUMN public.tbl_registra_items_checkmarx.num_surce_line IS '';
COMMENT ON COLUMN public.tbl_registra_items_checkmarx.nom_source_object IS '';
COMMENT ON COLUMN public.tbl_registra_items_checkmarx.nom_destination_folder IS '';
COMMENT ON COLUMN public.tbl_registra_items_checkmarx.nom_destination_filename IS '';
COMMENT ON COLUMN public.tbl_registra_items_checkmarx.num_destination_line IS '';
COMMENT ON COLUMN public.tbl_registra_items_checkmarx.nom_destination_object IS '';
COMMENT ON COLUMN public.tbl_registra_items_checkmarx.nom_result_state IS '';
COMMENT ON COLUMN public.tbl_registra_items_checkmarx.num_severity IS '';
COMMENT ON COLUMN public.tbl_registra_items_checkmarx.nom_result_severity IS '';
COMMENT ON COLUMN public.tbl_registra_items_checkmarx.fec_movto IS 'Fecha y hora de registro (guardada en automático)';
COMMENT ON COLUMN public.tbl_registra_items_checkmarx.keyx IS 'Indicador automático consecutivo de la tabla (autoincremental) (Primary Key)';

 --index

CREATE INDEX idx_tbl_registra_items_checkmarx_num_empleado ON tbl_registra_items_checkmarx (num_empleado);
CREATE INDEX idx_tbl_registra_items_checkmarx_id_proyecto ON tbl_registra_items_checkmarx (id_proyecto);
CREATE INDEX idx_tbl_registra_items_checkmarx_nom_proyecto ON tbl_registra_items_checkmarx (nom_proyecto);
CREATE INDEX idx_tbl_registra_items_checkmarx_keyx ON tbl_registra_items_checkmarx (keyx);

-- SELECT * FROM tbl_registra_items_checkmarx;
-- TRUNCATE TABLE public.tbl_registra_items_checkmarx;
-----------------------------------------------------------------------------------------------------------------------------

LENGUAJE|OCURRENCIAS|X_SEMANA|CANT_COLAB|TOT_SEM|TOT_DIAS|TOT_HORAS|FECHA_INI|FECHA_FIN|

----------------------------------------------------------------------------------------------------------------
-- DROP TABLE IF EXISTS public.tbl_registra_fecha_de_proyecto;
-- SELECT * FROM tbl_registra_fecha_de_proyecto;

CREATE TABLE IF NOT EXISTS public.tbl_registra_fecha_de_proyecto
(
    num_empleado bigint NOT NULL,
	id_proyecto bigint NOT NULL,
    --id_proyecto character varying(100) COLLATE pg_catalog."default" NOT NULL,
	nom_proyecto character varying(100) COLLATE pg_catalog."default" NOT NULL,
	nom_lenguaje character varying(30) COLLATE pg_catalog."default" NOT NULL,
	num_ocurrencias integer NOT NULL,
	num_por_semana integer NOT NULL,
	can_colaboradores integer NOT NULL,
	tot_semanal integer NOT NULL,
	tot_dias integer NOT NULL,
	tot_horas integer NOT NULL,
	fec_inicia_proyecto character varying(30) COLLATE pg_catalog."default" NOT NULL,
	fec_finaliza_proyecto character varying(30) COLLATE pg_catalog."default" NOT NULL,
	tot_dias_lun_a_vie integer NOT NULL, 
	fec_fin_proyecto_lun_a_vie character varying(30) COLLATE pg_catalog."default" NOT NULL,
    fec_movto timestamp without time zone NOT NULL DEFAULT now(),
    keyx serial NOT NULL,
    CONSTRAINT pk_tbl_registra_fecha_de_proyecto PRIMARY KEY (keyx)
) WITHOUT OIDS;

GRANT ALL ON TABLE public.tbl_registra_fecha_de_proyecto TO syscheckattendancebyface;
GRANT ALL ON TABLE public.tbl_registra_fecha_de_proyecto TO sysdesarrollorvia;

COMMENT ON TABLE public.tbl_registra_fecha_de_proyecto IS 'Datos de empleados y totales checkmarx de un proyecto';
COMMENT ON COLUMN public.tbl_registra_fecha_de_proyecto.num_empleado IS 'Número de empleado de la persona que ejecutó la aplicación';
COMMENT ON COLUMN public.tbl_registra_fecha_de_proyecto.id_proyecto IS 'ID del Proyecto';
COMMENT ON COLUMN public.tbl_registra_fecha_de_proyecto.nom_proyecto IS 'Nombre del Proyecto';
COMMENT ON COLUMN public.tbl_registra_fecha_de_proyecto.nom_lenguaje IS 'Nombre del lenguaje de trabajar';
COMMENT ON COLUMN public.tbl_registra_fecha_de_proyecto.num_ocurrencias IS 'Número de ocurrencias encontradas, sentencias + obsoleto + checkmarx';
COMMENT ON COLUMN public.tbl_registra_fecha_de_proyecto.num_por_semana IS 'Número de ocurrencias a trabajar por semana';
COMMENT ON COLUMN public.tbl_registra_fecha_de_proyecto.can_colaboradores IS 'Cantidad de colaboradores que estarán en el proyecto';
COMMENT ON COLUMN public.tbl_registra_fecha_de_proyecto.tot_semanal IS 'Total de ocurrencias a trabajar por semana según la métrica';
COMMENT ON COLUMN public.tbl_registra_fecha_de_proyecto.tot_dias IS 'Total de días que se llevará el desarrollo del proyecto';
COMMENT ON COLUMN public.tbl_registra_fecha_de_proyecto.tot_horas IS 'Total de horas que se llevará el desarrollo del proyecto';
COMMENT ON COLUMN public.tbl_registra_fecha_de_proyecto.fec_inicia_proyecto IS 'Fecha de inicio del proyecto';
COMMENT ON COLUMN public.tbl_registra_fecha_de_proyecto.fec_finaliza_proyecto IS 'Fecha que finaliza el proyecto';
COMMENT ON COLUMN public.tbl_registra_fecha_de_proyecto.tot_dias_lun_a_vie IS 'Total de días que se llevará el desarrollo del proyecto sin contar sábado y domingo';
COMMENT ON COLUMN public.tbl_registra_fecha_de_proyecto.fec_fin_proyecto_lun_a_vie IS 'Fecha que finaliza el proyecto sin contar sábado y domingo';
COMMENT ON COLUMN public.tbl_registra_fecha_de_proyecto.fec_movto IS 'Fecha y hora de registro (guardada en automático)';
COMMENT ON COLUMN public.tbl_registra_fecha_de_proyecto.keyx IS 'Indicador automático consecutivo de la tabla (autoincremental) (Primary Key)';

 --index

CREATE INDEX idx_tbl_registra_fecha_de_proyecto_num_empleado ON tbl_registra_fecha_de_proyecto (num_empleado);
CREATE INDEX idx_tbl_registra_fecha_de_proyecto_id_proyecto ON tbl_registra_fecha_de_proyecto (id_proyecto);
CREATE INDEX idx_tbl_registra_fecha_de_proyecto_nom_proyecto ON tbl_registra_fecha_de_proyecto (nom_proyecto);
CREATE INDEX idx_tbl_registra_fecha_de_proyecto_nom_lenguaje ON tbl_registra_fecha_de_proyecto (nom_lenguaje);
CREATE INDEX idx_tbl_registra_fecha_de_proyecto_keyx ON tbl_registra_fecha_de_proyecto (keyx);

-- SELECT * FROM tbl_registra_fecha_de_proyecto;
-- TRUNCATE TABLE public.tbl_registra_fecha_de_proyecto;
-----------------------------------------------------------------------------------------------------------------------------
SELECT * FROM tbl_registra_sentencias_ia WHERE id_proyecto = 786202403 AND nom_proyecto = 'cobrosproveedorintranet';
SELECT * FROM tbl_registra_obsoletos_ia WHERE id_proyecto = 786202403 AND nom_proyecto = 'cobrosproveedorintranet';
SELECT * FROM tbl_registra_totales_checkmarx WHERE id_proyecto = 786202403 AND nom_proyecto = 'cobrosproveedorintranet';
SELECT * FROM tbl_registra_items_checkmarx WHERE id_proyecto = 786202403 AND nom_proyecto = 'cobrosproveedorintranet';
SELECT * FROM tbl_registra_fecha_de_proyecto WHERE id_proyecto = 786202403 AND nom_proyecto = 'cobrosproveedorintranet';

------------------------------------------------------------------------------------------------------------------------------
-------------------------------------------------- TYPE ----------------------------------------------------------------------

-- Type: typ_metricas

-- DROP TYPE IF EXISTS public.typ_metricas;

CREATE TYPE public.typ_metricas AS
(
    mig_meta integer,
    vul_meta integer
);


-- Type: typ_token

-- DROP TYPE IF EXISTS public.typ_token CASCADE;

CREATE TYPE public.typ_token AS
(
    key_token character varying,
    fec_expira timestamp
);

ALTER TYPE public.typ_token
    OWNER TO syscheckattendancebyface;

------------------------------------------------------------------------------------------------------------------------------
-------------------------------------------------- FUNCIONES------------------------------------------------------------------

