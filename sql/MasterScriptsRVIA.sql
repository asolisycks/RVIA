-----------------------------------------------------------------------------------------------------------------
--------------------------------------------- CONTROLES ---------------------------------------------------------
-- Table: public.cat_centros
-- DROP TABLE IF EXISTS public.cat_centros CASCADE;
-- SELECT * FROM public.cat_centros;

CREATE TABLE IF NOT EXISTS public.cat_centros
(
    num_centro integer NOT NULL,
    nom_centro character varying(50) NOT NULL,
    fec_movto timestamp without time zone NOT NULL DEFAULT now(),
    keyx serial NOT NULL,
    CONSTRAINT pk_cat_centros PRIMARY KEY (keyx, num_centro),
    CONSTRAINT cat_centros_num_centro_key UNIQUE (num_centro)
) WITHOUT OIDS;

-- GRANT ALL ON TABLE public.cat_centros TO sysdesarrollorvia;
GRANT select, insert, update, delete ON TABLE public.cat_centros TO sysdesarrollorvia;

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

-- Index: idx_cat_centros_nom_centro
-- DROP INDEX IF EXISTS public.idx_cat_centros_nom_centro;
CREATE INDEX IF NOT EXISTS idx_cat_centros_nom_centro
    ON public.cat_centros USING btree
    (nom_centro COLLATE pg_catalog."default" ASC NULLS LAST)
    TABLESPACE pg_default;

-- Index: idx_cat_centros_num_centro
-- DROP INDEX IF EXISTS public.idx_cat_centros_num_centro;

CREATE INDEX IF NOT EXISTS idx_cat_centros_num_centro
    ON public.cat_centros USING btree
    (num_centro ASC NULLS LAST)
    TABLESPACE pg_default;

/*
INSERT INTO cat_centros (num_centro, nom_centro) VALUES ('0'::int, 'CERO'::varchar);
INSERT INTO cat_centros (num_centro, nom_centro) VALUES ('230190'::int, 'CLCN SIST PROG IV SERV FINANCIEROS'::varchar);
INSERT INTO cat_centros (num_centro, nom_centro) VALUES ('230578'::int, 'CLCN DESARROLLO SIST A+B VI'::varchar);
INSERT INTO cat_centros (num_centro, nom_centro) VALUES ('231637'::int, 'CLCN REMED DE VUL RETAIL'::varchar);
INSERT INTO cat_centros (num_centro, nom_centro) VALUES ('231639'::int, 'CLCN RV DESARROLLO RETAIL I'::varchar);
INSERT INTO cat_centros (num_centro, nom_centro) VALUES ('231640'::int, 'CLCN RV DESARROLLO RETAIL II'::varchar);
INSERT INTO cat_centros (num_centro, nom_centro) VALUES ('231641'::int, 'CLCN RV DESARROLLO RETAIL III'::varchar);
INSERT INTO cat_centros (num_centro, nom_centro) VALUES ('231642'::int, 'CLCN RV DESARROLLO RETAIL IV'::varchar);
INSERT INTO cat_centros (num_centro, nom_centro) VALUES ('231643'::int, 'CLCN RV DESARROLLO OM Y SF I'::varchar);
INSERT INTO cat_centros (num_centro, nom_centro) VALUES ('231644'::int, 'CLCN RV DESARROLLO OM Y SF II'::varchar);
INSERT INTO cat_centros (num_centro, nom_centro) VALUES ('231645'::int, 'CLCN RV DESARROLLO OM Y SF III'::varchar);
INSERT INTO cat_centros (num_centro, nom_centro) VALUES ('231646'::int, 'CLCN RV DESARROLLO OM Y SF IV'::varchar);
INSERT INTO cat_centros (num_centro, nom_centro) VALUES ('231649'::int, 'CLCN RV PROY INFRAESTRUCTURA'::varchar);
INSERT INTO cat_centros (num_centro, nom_centro) VALUES ('232390'::int, 'CLCN REMED DE VUL OMNIC Y SF'::varchar);
INSERT INTO cat_centros (num_centro, nom_centro) VALUES ('232490'::int, 'CLCN ANALISIS DE REQ AFORE'::varchar);
*/



----------------------------------------------------------------------------------
-- Table: public.cat_coordinadores
-- DROP TABLE IF EXISTS public.cat_coordinadores CASCADE;
-- SELECT * FROM public.cat_coordinadores;
CREATE TABLE IF NOT EXISTS public.cat_coordinadores
(
    num_coordinador bigint NOT NULL,
    nom_coordinador character varying(60) NOT NULL,
    fec_movto timestamp without time zone NOT NULL DEFAULT now(),
    keyx serial NOT NULL,
    CONSTRAINT pk_cat_coordinadores PRIMARY KEY (keyx, num_coordinador),
    CONSTRAINT cat_coordinadores_num_coordinador_key UNIQUE (num_coordinador)
) WITHOUT OIDS;

GRANT select, insert, update, delete ON TABLE public.cat_coordinadores TO sysdesarrollorvia;

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

INSERT INTO cat_coordinadores(num_coordinador, nom_coordinador) VALUES('0'::integer, 'cero'::varchar);
INSERT INTO cat_coordinadores(num_coordinador, nom_coordinador) VALUES('91080819'::integer, 'Gilberto Valenzuela Alvarez'::varchar);
INSERT INTO cat_coordinadores(num_coordinador, nom_coordinador) VALUES('91452716'::integer, 'Georgina Maria Del Rosario Gerardo Diaz'::varchar);
INSERT INTO cat_coordinadores(num_coordinador, nom_coordinador) VALUES('90035135'::integer, 'Oscar Alberto Aguilar Aramburo'::varchar);
INSERT INTO cat_coordinadores(num_coordinador, nom_coordinador) VALUES('91187631'::integer, 'Rolando Ponce de León Araujo'::varchar);

----------------------------------------------------------------------------------

-- Table: public.cat_divisionales
-- DROP TABLE IF EXISTS public.cat_divisionales CASCADE;
-- SELECT * FROM public.cat_divisionales;
CREATE TABLE IF NOT EXISTS public.cat_divisionales
(
    num_divisional bigint NOT NULL,
    nom_divisional character varying(60) COLLATE pg_catalog."default" NOT NULL,
    fec_movto timestamp without time zone NOT NULL DEFAULT now(),
    keyx serial NOT NULL,
    CONSTRAINT pk_cat_divisionales PRIMARY KEY (keyx, num_divisional),
    CONSTRAINT cat_divisionales_num_divisional_key UNIQUE (num_divisional)
) WITHOUT OIDS;

GRANT select, insert, update, delete ON TABLE public.cat_divisionales TO sysdesarrollorvia;

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


INSERT INTO cat_divisionales (num_divisional, nom_divisional) VALUES('90017854'::bigint, 'José Guadalupe Mendoza Macías'::varchar);
INSERT INTO cat_divisionales (num_divisional, nom_divisional) VALUES('90028058'::bigint, ' Jesús Arnoldo Vargas Borboa'::varchar);

----------------------------------------------------------------------------------

-- Table: public.cat_gerentes
-- DROP TABLE IF EXISTS public.cat_gerentes CASCADE;
-- SELECT * FROM public.cat_gerentes;
CREATE TABLE IF NOT EXISTS public.cat_gerentes
(
    num_gerente bigint NOT NULL,
    nom_gerente character varying(60) COLLATE pg_catalog."default" NOT NULL,
    fec_movto timestamp without time zone NOT NULL DEFAULT now(),
    keyx serial NOT NULL,
    CONSTRAINT pk_cat_gerentes PRIMARY KEY (keyx, num_gerente),
    CONSTRAINT cat_gerentes_num_gerente_key UNIQUE (num_gerente)
) WITHOUT OIDS;

GRANT select, insert, update, delete ON TABLE public.cat_gerentes TO sysdesarrollorvia;

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

INSERT INTO cat_gerentes(num_gerente, nom_gerente) VALUES('0'::integer, 'Cero'::varchar);
INSERT INTO cat_gerentes(num_gerente, nom_gerente) VALUES('90329121'::integer, 'José Arturo Solís Ramírez'::varchar);
INSERT INTO cat_gerentes(num_gerente, nom_gerente) VALUES('96665701'::integer, 'Cristabel Silva Barraza'::varchar);
INSERT INTO cat_gerentes(num_gerente, nom_gerente) VALUES('92474934'::integer, 'Marcos Antonio Cuevas Rodríguez'::varchar);
INSERT INTO cat_gerentes(num_gerente, nom_gerente) VALUES('95657861'::integer, 'Yareli Lizeth Calderon Coronel'::varchar);
INSERT INTO cat_gerentes(num_gerente, nom_gerente) VALUES('92102115'::integer, 'Claudia Batiz Beltrán'::varchar);
INSERT INTO cat_gerentes(num_gerente, nom_gerente) VALUES('92853341'::integer, 'Roberto Carlos Santillán Torres'::varchar);
INSERT INTO cat_gerentes(num_gerente, nom_gerente) VALUES('94812519'::integer, 'Teofilo Inzunza Payán'::varchar);
INSERT INTO cat_gerentes(num_gerente, nom_gerente) VALUES('94353638'::integer, 'Ruben Octavio Manjarrez Hernández'::varchar);
INSERT INTO cat_gerentes(num_gerente, nom_gerente) VALUES('91712467'::integer, 'José Rodolfo Uriarte Ramírez'::varchar);
INSERT INTO cat_gerentes(num_gerente, nom_gerente) VALUES('95555897'::integer, 'Sofia Carrazco Valenzuela'::varchar);

----------------------------------------------------------------------------------

-- Table: public.cat_nacionales
-- DROP TABLE IF EXISTS public.cat_nacionales CASCADE;
-- SELECT * FROM public.cat_nacionales;
CREATE TABLE IF NOT EXISTS public.cat_nacionales
(
    num_nacional bigint NOT NULL,
    nom_nacional character varying(60) NOT NULL,
    fec_movto timestamp without time zone NOT NULL DEFAULT now(),
    keyx serial NOT NULL,
    CONSTRAINT pk_cat_nacionales PRIMARY KEY (keyx, num_nacional),
    CONSTRAINT cat_nacionales_num_nacional_key UNIQUE (num_nacional)
) WITHOUT OIDS;

GRANT select, insert, update, delete ON TABLE public.cat_nacionales TO sysdesarrollorvia;

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

INSERT INTO cat_nacionales(num_nacional, nom_nacional) VALUES('96652551'::integer, 'Teresa Guadalupe Gálvez Gastelum'::varchar);
INSERT INTO cat_nacionales(num_nacional, nom_nacional) VALUES('90203224'::integer, 'Héctor Antonio Cruz Zazueta'::varchar);

----------------------------------------------------------------------------------
-- Table: public.cat_proveedores
-- DROP TABLE IF EXISTS public.cat_proveedores CASCADE;
-- SELECT * FROM public.cat_proveedores;

CREATE TABLE IF NOT EXISTS public.cat_proveedores
(
    num_proveedor smallint NOT NULL,
    nom_proveedor character varying(50) NOT NULL,
    fec_movto timestamp without time zone NOT NULL DEFAULT now(),
    keyx serial NOT NULL,
    CONSTRAINT pk_cat_proveedores PRIMARY KEY (keyx, num_proveedor),
    CONSTRAINT cat_proveedores_num_proveedor_key UNIQUE (num_proveedor)
) WITHOUT OIDS;

GRANT select, insert, update, delete ON TABLE public.cat_proveedores TO sysdesarrollorvia;

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

INSERT INTO cat_proveedores (num_proveedor, nom_proveedor) VALUES ('0'::smallint, 'Cero'::varchar);
INSERT INTO cat_proveedores (num_proveedor, nom_proveedor) VALUES ('1'::smallint, 'Softtek'::varchar);
INSERT INTO cat_proveedores (num_proveedor, nom_proveedor) VALUES ('2'::smallint, 'Neoris'::varchar);
INSERT INTO cat_proveedores (num_proveedor, nom_proveedor) VALUES ('3'::smallint, 'AP Interfaces'::varchar);
INSERT INTO cat_proveedores (num_proveedor, nom_proveedor) VALUES ('4'::smallint, 'Coppel'::varchar);
INSERT INTO cat_proveedores (num_proveedor, nom_proveedor) VALUES ('5'::smallint, 'Kairos'::varchar);

----------------------------------------------------------------------------------

-- Table: public.cat_puestos
-- DROP TABLE IF EXISTS public.cat_puestos CASCADE;
-- SELECT * FROM public.cat_puestos;

CREATE TABLE IF NOT EXISTS public.cat_puestos
(
    num_puesto smallint NOT NULL,
    nom_puesto character varying(50) NOT NULL,
    fec_movto timestamp without time zone NOT NULL DEFAULT now(),
    keyx serial NOT NULL,
    CONSTRAINT pk_cat_puestos PRIMARY KEY (keyx, num_puesto),
    CONSTRAINT cat_puestos_num_puesto_key UNIQUE (num_puesto)
) WITHOUT OIDS;

GRANT select, insert, update, delete ON TABLE public.cat_puestos TO sysdesarrollorvia;

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

INSERT INTO cat_puestos (num_puesto, nom_puesto) VALUES ('0'::smallint, 'CERO'::varchar);
INSERT INTO cat_puestos (num_puesto, nom_puesto) VALUES ('37'::smallint, 'ENTRENAMIENTO'::varchar);
INSERT INTO cat_puestos (num_puesto, nom_puesto) VALUES ('42'::smallint, 'JEFE'::varchar);
INSERT INTO cat_puestos (num_puesto, nom_puesto) VALUES ('077'::smallint, 'PROGRAMADOR'::varchar);
INSERT INTO cat_puestos (num_puesto, nom_puesto) VALUES ('134'::smallint, 'GTE. DE PROYECTOS'::varchar);
INSERT INTO cat_puestos (num_puesto, nom_puesto) VALUES ('364'::smallint, 'GERENTE DE DESARROLLO'::varchar);
INSERT INTO cat_puestos (num_puesto, nom_puesto) VALUES ('442'::smallint, 'TESTER'::varchar);
INSERT INTO cat_puestos (num_puesto, nom_puesto) VALUES ('444'::smallint, 'ARQUITECTO DE SOFTWARE'::varchar);
INSERT INTO cat_puestos (num_puesto, nom_puesto) VALUES ('136'::smallint, 'LÍDER DE PROYECTO'::varchar);
-- INSERT INTO cat_puestos (num_puesto, nom_puesto) VALUES (''::smallint, 'ANALISTA DE SISTEMAS'::varchar);

------------------------------------------------------------------------------------------------------------------------------
-- Table: public.cat_colaboradores
-- DROP TABLE IF EXISTS public.cat_colaboradores CASCADE;
-- SELECT * FROM public.cat_colaboradores;

CREATE TABLE IF NOT EXISTS public.cat_colaboradores
(
    num_colaborador bigint NOT NULL,
    nom_colaborador character varying(60) NOT NULL,
    num_puesto smallint NOT NULL,
    num_centro integer NOT NULL,
    num_proveedor smallint NOT NULL,
    num_gerente bigint NOT NULL,
    num_coordinador bigint NOT NULL,
    fec_movto timestamp without time zone NOT NULL DEFAULT now(),
    keyx serial NOT NULL,
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
) WITHOUT OIDS;

GRANT select, insert, update, delete ON TABLE public.cat_colaboradores TO sysdesarrollorvia;

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


-- INSERT INTO cat_colaboradores (num_colaborador, nom_colaborador, num_puesto, num_centro, num_proveedor, num_gerente, num_coordinador ) VALUES('97290645'::integer, 'Carmen Maria Carrillo Gonzalez'::varchar, '136'::smallint, '231644'::integer, '4'::smallint, '90329121'::integer, '91080819'::integer );
-- INSERT INTO cat_colaboradores (num_colaborador, nom_colaborador, num_puesto, num_centro, num_proveedor, num_gerente, num_coordinador ) VALUES('96665701'::integer, 'Cristabel Silva Barraza'::varchar, '136'::smallint, '231643'::integer, '4'::smallint, '96665701'::integer, '91080819'::integer );
-- INSERT INTO cat_colaboradores (num_colaborador, nom_colaborador, num_puesto, num_centro, num_proveedor, num_gerente, num_coordinador ) VALUES('92474934'::integer, 'Marcos Antonio Cuevas Rodríguez'::varchar, '136'::smallint, '231646'::integer, '4'::smallint, '92474934'::integer, '91452716'::integer );
-- INSERT INTO cat_colaboradores (num_colaborador, nom_colaborador, num_puesto, num_centro, num_proveedor, num_gerente, num_coordinador ) VALUES('95657861'::integer, 'Yareli Lizeth Calderon Coronel'::varchar, '136'::smallint, '231645'::integer, '4'::smallint, '95657861'::integer, '91452716'::integer );
-- INSERT INTO cat_colaboradores (num_colaborador, nom_colaborador, num_puesto, num_centro, num_proveedor, num_gerente, num_coordinador ) VALUES('92102115'::integer, 'Claudia Batiz Beltrán'::varchar, '136'::smallint, '231649'::integer, '4'::smallint, '92102115'::integer, '91452716'::integer );
-- INSERT INTO cat_colaboradores (num_colaborador, nom_colaborador, num_puesto, num_centro, num_proveedor, num_gerente, num_coordinador ) VALUES('92853341'::integer, 'Roberto Carlos Santillán Torres'::varchar, '136'::smallint, '231639'::integer, '4'::smallint, '92853341'::integer, '90035135'::integer );
-- INSERT INTO cat_colaboradores (num_colaborador, nom_colaborador, num_puesto, num_centro, num_proveedor, num_gerente, num_coordinador ) VALUES('94812519'::integer, 'Teofilo Inzunza Payán'::varchar, '136'::smallint, '231640'::integer, '4'::smallint, '94812519'::integer, '90035135'::integer );
-- INSERT INTO cat_colaboradores (num_colaborador, nom_colaborador, num_puesto, num_centro, num_proveedor, num_gerente, num_coordinador ) VALUES('94353638'::integer, 'Ruben Octavio Manjarrez Hernández'::varchar, '136'::smallint, '231641'::integer, '4'::smallint, '94353638'::integer, '90035313'::integer );
-- INSERT INTO cat_colaboradores (num_colaborador, nom_colaborador, num_puesto, num_centro, num_proveedor, num_gerente, num_coordinador ) VALUES('91712467'::integer, 'José Rodolfo Uriarte Ramírez'::varchar, '136'::smallint, '231642'::integer, '4'::smallint, '91712467'::integer, '90035313'::integer );


----------------------------------------------------------------------------------

-- DROP TABLE IF EXISTS public.ctl_token_ia CASCADE;
-- SELECT * FROM ctl_token_ia;
-- TRUNCATE TABLE ctl_token_ia;
-- SELECT fun_registrar_token( '90329121'::BIGINT, '367cfa3ebdbbf8a41b0b4d57d213d82c96f1bbd95c9074a8aef33e7782eb456c'::VARCHAR );

CREATE TABLE IF NOT EXISTS public.ctl_token_ia
(
    num_empleado bigint NOT NULL,
    key_token character varying(200) NOT NULL,
	fec_expira timestamp NOT NULL,
    fec_movto timestamp  WITHOUT Time zone NOT NULL DEFAULT now(),
    keyx serial NOT NULL,
    CONSTRAINT pk_ctl_token_ia PRIMARY KEY (keyx)
) WITHOUT OIDS;

GRANT select, insert, update, delete ON TABLE public.ctl_token_ia TO syscheckattendancebyface;
GRANT select, insert, update, delete ON TABLE public.ctl_token_ia TO sysdesarrollorvia;

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
-- DROP TABLE IF EXISTS public.ctl_proyectos CASCADE;
-- SELECT * FROM ctl_proyectos WHERE id_proyecto = 371202404;

CREATE TABLE IF NOT EXISTS public.ctl_proyectos
(
    num_empleado bigint NOT NULL,
	id_proyecto bigint NOT NULL,
	nom_proyecto character varying(100) NOT NULL,
	flg_con_ia integer NOT NULL,
	fec_movto timestamp without time zone NOT NULL DEFAULT now(),
    keyx serial NOT NULL,
    CONSTRAINT pk_ctl_proyectos PRIMARY KEY (keyx)
) WITHOUT OIDS;

GRANT select, insert, update, delete ON TABLE public.ctl_proyectos TO syscheckattendancebyface;
GRANT select, insert, update, delete ON TABLE public.ctl_proyectos TO sysdesarrollorvia;

COMMENT ON TABLE public.ctl_proyectos IS 'Datos de empleados y control de proyectos que fueron o no pasados por la IA';
COMMENT ON COLUMN public.ctl_proyectos.num_empleado IS 'Número de empleado de la persona que ejecutó la aplicación';
COMMENT ON COLUMN public.ctl_proyectos.id_proyecto IS 'ID del Proyecto';
COMMENT ON COLUMN public.ctl_proyectos.flg_con_ia IS 'Flag que identifica 0 = sin IA 1 = Con IA';
COMMENT ON COLUMN public.ctl_proyectos.nom_proyecto IS 'Nombre del Proyecto';
COMMENT ON COLUMN public.ctl_proyectos.fec_movto IS 'Fecha y hora de registro (guardada en automático)';
COMMENT ON COLUMN public.ctl_proyectos.keyx IS 'Indicador automático consecutivo de la tabla (autoincremental) (Primary Key)';

 --index

CREATE INDEX idx_ctl_proyectos_num_empleado ON ctl_proyectos (num_empleado);
CREATE INDEX idx_ctl_proyectos_id_proyecto ON ctl_proyectos (id_proyecto);
CREATE INDEX idx_ctl_proyectos_nom_proyecto ON ctl_proyectos (nom_proyecto);
CREATE INDEX idx_ctl_proyectos_keyx ON ctl_proyectos (keyx);

-- SELECT * FROM ctl_proyectos;
-- TRUNCATE TABLE public.ctl_proyectos;
-----------------------------------------------------------------------------------------------------------------------------

----------------------------------------------------------------------------------------------------------------
-- DROP TABLE IF EXISTS public.tbl_registra_totales CASCADE;
-- SELECT * FROM tbl_registra_totales WHERE id_proyecto = 158202403;

CREATE TABLE IF NOT EXISTS public.tbl_registra_totales
(
    num_empleado bigint NOT NULL,
	id_proyecto bigint NOT NULL,
	nom_proyecto character varying(100) NOT NULL,
	nom_language character varying(30) NOT NULL,
	num_files integer NOT NULL,
	num_blank integer NOT NULL,
	num_comment integer NOT NULL,
	num_code integer NOT NULL,
	fec_movto timestamp without time zone NOT NULL DEFAULT now(),
    keyx serial NOT NULL,
    CONSTRAINT pk_tbl_registra_totales PRIMARY KEY (keyx)
) WITHOUT OIDS;

GRANT select, insert, update, delete ON TABLE public.tbl_registra_totales TO syscheckattendancebyface;
GRANT select, insert, update, delete ON TABLE public.tbl_registra_totales TO sysdesarrollorvia;

COMMENT ON TABLE public.tbl_registra_totales IS 'Datos de empleados y totales checkmarx de un proyecto';
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

-- DROP TABLE IF EXISTS public.tbl_registra_sentencias_ia CASCADE;
-- TRUNCATE TABLE public.tbl_registra_sentencias_ia;

-- SELECT * FROM tbl_registra_sentencias_ia WHERE id_proyecto = 158202403;

CREATE TABLE IF NOT EXISTS public.tbl_registra_sentencias_ia
(
    num_empleado bigint NOT NULL,
	id_proyecto bigint NOT NULL,
	--id_proyecto character varying(100) COLLATE pg_catalog."default" NOT NULL,
    nom_proyecto character varying(100) NOT NULL,
    nom_archivo character varying(300) NOT NULL,
    num_linea integer NOT NULL,
    dat_sentencia character varying(1000) NOT NULL,
    fec_movto timestamp without time zone NOT NULL DEFAULT now(),
    keyx serial NOT NULL,
    CONSTRAINT pk_tbl_registra_sentencias_ia PRIMARY KEY (keyx)
) WITHOUT OIDS;

GRANT select, insert, update, delete ON TABLE public.tbl_registra_sentencias_ia TO syscheckattendancebyface;
GRANT select, insert, update, delete ON TABLE public.tbl_registra_sentencias_ia TO sysdesarrollorvia;

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

CREATE INDEX idx_tbl_registra_sentencias_ia_num_empleado ON tbl_registra_sentencias_ia (num_empleado);
CREATE INDEX idx_tbl_registra_sentencias_ia_id_proyecto ON tbl_registra_sentencias_ia (id_proyecto);
CREATE INDEX idx_tbl_registra_sentencias_ia_nom_proyecto ON tbl_registra_sentencias_ia (nom_proyecto);
CREATE INDEX idx_tbl_registra_sentencias_ia_keyx ON tbl_registra_sentencias_ia (keyx);

-- SELECT * FROM tbl_registra_sentencias_ia;
----------------------------------------------------------------------------------------------------------------
-- DROP TABLE IF EXISTS public.tbl_registra_obsoletos_ia CASCADE;
-- SELECT * FROM tbl_registra_obsoletos_ia WHERE id_proyecto = 158202403;

CREATE TABLE IF NOT EXISTS public.tbl_registra_obsoletos_ia
(
    num_empleado bigint NOT NULL,
	id_proyecto bigint NOT NULL,
	-- id_proyecto character varying(100) COLLATE pg_catalog."default" NOT NULL,
    nom_proyecto character varying(100) NOT NULL,
    nom_archivo character varying(300)  NOT NULL,
    num_linea integer NOT NULL,
    dat_obsoleto character varying(1000) NOT NULL,
    fec_movto timestamp without time zone NOT NULL DEFAULT now(),
    keyx serial NOT NULL,
    CONSTRAINT pk_tbl_registra_obsoletos_ia PRIMARY KEY (keyx)
) WITHOUT OIDS;

GRANT select, insert, update, delete ON TABLE public.tbl_registra_obsoletos_ia TO syscheckattendancebyface;
GRANT select, insert, update, delete ON TABLE public.tbl_registra_obsoletos_ia TO sysdesarrollorvia;

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
	ext_lenguaje character (20) NOT NULL,
    pmt_texto character varying(400000) NOT NULL,
	nom_model character (20) NOT NULL,
	flg_activo integer NOT NULL DEFAULT 0,
    fec_movto timestamp without time zone NOT NULL DEFAULT now(),
    keyx serial NOT NULL,
    CONSTRAINT pk_ctl_prompt PRIMARY KEY (keyx)
) WITHOUT OIDS;

GRANT select, insert, update, delete ON TABLE public.ctl_prompt TO syscheckattendancebyface;
GRANT select, insert, update, delete ON TABLE public.ctl_prompt TO sysdesarrollorvia;

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
Fixed code: <Rewritten code between three quotes ```PHP at the beginning of the code and ``` at the end of the code.>
Send the output in spanish', 'ADVANCED');

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
-- DROP TABLE IF EXISTS public.tbl_registra_totales_checkmarx CASCADE;
-- SELECT * FROM tbl_registra_totales_checkmarx WHERE id_proyecto = 158202403;

CREATE TABLE IF NOT EXISTS public.tbl_registra_totales_checkmarx
(
    num_empleado bigint NOT NULL,
	id_proyecto bigint NOT NULL,
    --id_proyecto character varying(100) COLLATE pg_catalog."default" NOT NULL,
	nom_proyecto character varying(100) NOT NULL,
    num_high integer NOT NULL,
	num_medium integer NOT NULL,
	num_low integer NOT NULL,
    fec_movto timestamp without time zone NOT NULL DEFAULT now(),
    keyx serial NOT NULL,
    CONSTRAINT pk_tbl_registra_totales_checkmarx PRIMARY KEY (keyx)
) WITHOUT OIDS;

GRANT select, insert, update, delete ON TABLE public.tbl_registra_totales_checkmarx TO syscheckattendancebyface;
GRANT select, insert, update, delete ON TABLE public.tbl_registra_totales_checkmarx TO sysdesarrollorvia;

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
-- SELECT keyx, * FROM tbl_registra_items_checkmarx  WHERE id_proyecto = 158202403;

CREATE TABLE IF NOT EXISTS public.tbl_registra_items_checkmarx
(
    num_empleado bigint NOT NULL,
	id_proyecto bigint NOT NULL,
    --id_proyecto character varying(100) NOT NULL,
	nom_proyecto character varying(100)  NOT NULL,
	num_id integer NOT NULL,
	fec_detection_date character varying(30) NOT NULL,
	rut_direct_link character varying(200) NOT NULL,
	fun_query_name character varying(100) NOT NULL,
	nom_source_folder character varying(200) NOT NULL, 
	nom_source_filename character varying(100) NOT NULL, 
	num_surce_line character varying(10)  NOT NULL, 
	nom_source_object character varying(100) NOT NULL,
	nom_destination_folder character varying(100) NOT NULL, 
	nom_destination_filename character varying(100) NOT NULL, 
	num_destination_line character varying(10) NOT NULL, 
	nom_destination_object character varying(100) NOT NULL, 
	nom_result_state character varying(50) NOT NULL, 
	num_severity character varying(10) NOT NULL,
	nom_result_severity character varying(10) NOT NULL,
    fec_movto timestamp without time zone NOT NULL DEFAULT now(),
    keyx serial NOT NULL,
    CONSTRAINT pk_tbl_registra_items_checkmarx PRIMARY KEY (keyx)
) WITHOUT OIDS;

GRANT select, insert, update, delete ON TABLE public.tbl_registra_items_checkmarx TO syscheckattendancebyface;
GRANT select, insert, update, delete ON TABLE public.tbl_registra_items_checkmarx TO sysdesarrollorvia;

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
-- SELECT * FROM tbl_registra_fecha_de_proyecto WHERE id_proyecto = 158202403;

CREATE TABLE IF NOT EXISTS public.tbl_registra_fecha_de_proyecto
(
    num_empleado bigint NOT NULL,
	id_proyecto bigint NOT NULL,
    --id_proyecto character varying(100) COLLATE pg_catalog."default" NOT NULL,
	nom_proyecto character varying(100) NOT NULL,
	nom_lenguaje character varying(30) NOT NULL,
	num_ocurrencias integer NOT NULL,
	num_por_semana integer NOT NULL,
	can_colaboradores integer NOT NULL,
	tot_semanal integer NOT NULL,
	tot_dias integer NOT NULL,
	tot_horas integer NOT NULL,
	fec_inicia_proyecto character varying(30) NOT NULL,
	fec_finaliza_proyecto character varying(30) NOT NULL,
	tot_dias_lun_a_vie integer NOT NULL, 
	fec_fin_proyecto_lun_a_vie character varying(30) NOT NULL,
    fec_movto timestamp without time zone NOT NULL DEFAULT now(),
    keyx serial NOT NULL,
    CONSTRAINT pk_tbl_registra_fecha_de_proyecto PRIMARY KEY (keyx)
) WITHOUT OIDS;

GRANT select, insert, update, delete ON TABLE public.tbl_registra_fecha_de_proyecto TO syscheckattendancebyface;
GRANT select, insert, update, delete ON TABLE public.tbl_registra_fecha_de_proyecto TO sysdesarrollorvia;

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

----------------------------------------------------------------------------------------------------------------
-- ARCHIVO|LINT_CHECK_BEFORE|HORA_INICIO|HORA_FIN|TIEMPO_EN_SEGUNDOS|TIEMPO_EN_MINUTOS|RESPUESTA_LINT|LINT_CHECK_AFTER|COMENTARIOS_BITO
-- DROP TABLE IF EXISTS public.tbl_registra_bito_ia CASCADE;
-- SELECT * FROM tbl_registra_bito_ia WHERE id_proyecto = '193202404' ORDER BY keyX;
-- SELECT * FROM tbl_registra_bito_ia ORDER BY keyX;

CREATE TABLE IF NOT EXISTS public.tbl_registra_bito_ia
(
    num_empleado bigint NOT NULL,
	id_proyecto bigint NOT NULL,
	nom_proyecto character varying(100) NOT NULL,
    arc_proyecto character varying(300) NOT NULL DEFAULT '',
	lnt_antes character varying(15) NOT NULL DEFAULT '',
	hra_inicia_proyecto character varying(30) NOT NULL DEFAULT '',
	hra_finaliza_proyecto character varying(30) NOT NULL DEFAULT '',
	tpo_segundos character varying(15) NOT NULL DEFAULT '',
	tpo_minutos character varying(15) NOT NULL DEFAULT '',
	lnt_despues character varying(15) NOT NULL DEFAULT '',
	lnt_descripcion character varying (500) NOT NULL DEFAULT '',
	com_bito TEXT,
    fec_movto timestamp without time zone NOT NULL DEFAULT now(),
    keyx serial NOT NULL,
    CONSTRAINT pk_tbl_registra_bito_ia PRIMARY KEY (keyx)
) WITHOUT OIDS;

GRANT select, insert, update, delete ON TABLE public.tbl_registra_bito_ia TO syscheckattendancebyface;
GRANT select, insert, update, delete ON TABLE public.tbl_registra_bito_ia TO sysdesarrollorvia;

COMMENT ON TABLE public.tbl_registra_bito_ia IS 'Datos del proyecto y respuesta de BITO';
COMMENT ON COLUMN public.tbl_registra_bito_ia.num_empleado IS 'Número de empleado de la persona que ejecutó la aplicación';
COMMENT ON COLUMN public.tbl_registra_bito_ia.id_proyecto IS 'ID del Proyecto';
COMMENT ON COLUMN public.tbl_registra_bito_ia.nom_proyecto IS 'Nombre del Proyecto';
COMMENT ON COLUMN public.tbl_registra_bito_ia.arc_proyecto IS 'Ruta y archivo que se procesó';
COMMENT ON COLUMN public.tbl_registra_bito_ia.lnt_antes IS 'Estatus de ejecución del linter antes de pasar por BITO (CORRECTO o INCORRECTO)';
COMMENT ON COLUMN public.tbl_registra_bito_ia.hra_inicia_proyecto IS 'Hora de inicio de procesar con BITO';
COMMENT ON COLUMN public.tbl_registra_bito_ia.hra_finaliza_proyecto IS 'Hora de finalización de procesar con BITO';
COMMENT ON COLUMN public.tbl_registra_bito_ia.tpo_segundos IS 'Tiempo que se llevó de procesar con BITO en segundos';
COMMENT ON COLUMN public.tbl_registra_bito_ia.tpo_minutos IS 'Tiempo que se llevó de procesar con BITO en minutos';
COMMENT ON COLUMN public.tbl_registra_bito_ia.lnt_despues IS 'Estatus de ejecución del linter después de pasar por BITO (CORRECTO o INCORRECTO)';
COMMENT ON COLUMN public.tbl_registra_bito_ia.lnt_descripcion IS 'Descripción del resultado de pasar por el linter';
COMMENT ON COLUMN public.tbl_registra_bito_ia.com_bito IS 'Comentarios o sugerencias que nos proporciona la IA para el tratado del archivo';
COMMENT ON COLUMN public.tbl_registra_bito_ia.fec_movto IS 'Fecha y hora de primer registro (guardada en automático)';
COMMENT ON COLUMN public.tbl_registra_bito_ia.keyx IS 'Indicador automático consecutivo de la tabla (autoincremental) (Primary Key)';

 --index

CREATE INDEX idx_tbl_registra_bito_ia_num_emppleado ON tbl_registra_bito_ia (num_empleado);
CREATE INDEX idx_tbl_registra_bito_ia_id_proyecto ON tbl_registra_bito_ia (id_proyecto);
CREATE INDEX idx_tbl_registra_bito_ia_nom_proyecto ON tbl_registra_bito_ia (nom_proyecto);
CREATE INDEX idx_tbl_registra_bito_ia_keyx ON tbl_registra_bito_ia (keyx);

-- SELECT * FROM tbl_registra_bito_ia;
-- TRUNCATE TABLE public.tbl_registra_bito_ia;
-----------------------------------------------------------------------------------------------------------------------------

CREATE TABLE IF NOT EXISTS public.ctl_q_table 
(
	nom_language character varying(30) NOT NULL,
    tipo_de_problema character varying(255) NOT NULL,
    recompensa integer NOT NULL,
	fec_movto timestamp without time zone NOT NULL DEFAULT now(),
	flg_activo smallint NOT NULL DEFAULT 0,
    keyx serial NOT NULL,
    CONSTRAINT pk_ctl_q_table PRIMARY KEY (keyx)
);

GRANT select, insert, update, delete ON TABLE public.ctl_q_table TO syscheckattendancebyface;
GRANT select, insert, update, delete ON TABLE public.ctl_q_table TO sysdesarrollorvia;

COMMENT ON TABLE public.ctl_q_table IS 'Esta tabla muestra las recompensas asociadas con cada tipo de problema que puedes encontrar durante la revisión del código.';
COMMENT ON COLUMN public.ctl_q_table_ia.nom_language IS 'Nombre del lenguaje de programación';
COMMENT ON COLUMN public.ctl_q_table_ia.tipo_de_problema IS 'Descripción del problema a evaluar';
COMMENT ON COLUMN public.ctl_q_table_ia.recompensa IS 'Valor de la recompensa de -5 a +5';
COMMENT ON COLUMN public.ctl_q_table_ia.fec_movto IS 'Fecha y hora de primer registro (guardada en automático)';
COMMENT ON COLUMN public.ctl_q_table_ia.keyx IS 'Indicador automático consecutivo de la tabla (autoincremental) (Primary Key)';

-- INDEX --

CREATE INDEX idx_ctl_q_table_ia_nom_language ON tbl_registra_bito_ia (nom_language);
CREATE INDEX idx_ctl_q_table_ia_tipo_de_problema ON tbl_registra_bito_ia (tipo_de_problema);
CREATE INDEX idx_ctl_q_table_ia_recompensa ON tbl_registra_bito_ia (recompensa);
CREATE INDEX idx_ctl_q_table_ia_keyx ON tbl_registra_bito_ia (keyx);


------------------------------------------------------------------------------------------------------------------------------
-------------------------------------------------- FUNCIONES------------------------------------------------------------------

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

------------------------------------------------------------------------------------------------------------------------------

-- FUNCTION: public.fun_obtener_prompt(character, character, character)

-- DROP FUNCTION IF EXISTS public.fun_obtener_prompt(character, character, character);
-- SELECT * FROM ctl_prompt;
-- SELECT pmt_texto FROM ctl_prompt WHERE nom_cliente_ia = 'BITO' AND ext_lenguaje = 'PHP' AND nom_model = 'ADVANCED' AND flg_activo = 0;
-- SELECT fun_obtener_prompt('BITO', 'PHP', 'ADVANCED');


CREATE OR REPLACE FUNCTION public.fun_obtener_prompt(
	character,
	character,
	character)
    RETURNS SETOF character varying 
    LANGUAGE 'plpgsql'
    COST 100
    VOLATILE PARALLEL UNSAFE
    ROWS 1000

AS $BODY$

DECLARE
	cNomCliente		ALIAS FOR $1;
	cLenguaje		ALIAS FOR $2;
	cModel			ALIAS FOR $3;
	
	Tokens      typ_token;
	recTokens	RECORD;
BEGIN

	RETURN QUERY SELECT pmt_texto FROM ctl_prompt WHERE nom_cliente_ia = $1 AND ext_lenguaje = $2 AND nom_model = $3 AND flg_activo = 0;
	
	--IF NOT FOUND THEN
	--	RAISE EXCEPTION 'No name at %.', $1;
	--END IF;
	
	RETURN;
END
$BODY$;

------------------------------------------------------------------------------------------------------------------------------

-- FUNCTION: public.fun_obtener_token(bigint, character varying)
-- DROP FUNCTION IF EXISTS public.fun_obtener_token(bigint, character varying);

CREATE OR REPLACE FUNCTION public.fun_obtener_token(
	bigint,
	character varying)
    RETURNS SETOF typ_token
    LANGUAGE 'plpgsql'
    COST 100
    VOLATILE PARALLEL UNSAFE
    ROWS 1000

AS $BODY$

DECLARE
	lNumero		ALIAS FOR $1;
	cToken		ALIAS FOR $2;	
	
	Tokens      typ_token;
	recTokens	RECORD;
BEGIN
	FOR recTokens IN
		SELECT key_token, fec_expira FROM ctl_token_ia WHERE num_empleado = $1::bigint AND key_token = $2::character varying ORDER BY keyx DESC LIMIT 1
	LOOP
		Tokens.key_token 	:= recTokens.key_token;
		Tokens.fec_expira	:= recTokens.fec_expira;
		
		RETURN NEXT Tokens;
	END LOOP;
END
$BODY$;

------------------------------------------------------------------------------------------------------------------------------
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

------------------------------------------------------------------------------------------------------------------------------

-- FUNCTION: public.fun_registrar_items_checkmarx(bigint, bigint, character varying, integer, character varying, character varying, character varying, character varying, character varying, character varying, character varying, character varying, character varying, character varying, character varying, character varying, character varying, character varying)

-- DROP FUNCTION IF EXISTS public.fun_registrar_items_checkmarx(bigint, bigint, character varying, integer, character varying, character varying, character varying, character varying, character varying, character varying, character varying, character varying, character varying, character varying, character varying, character varying, character varying, character varying);

CREATE OR REPLACE FUNCTION public.fun_registrar_items_checkmarx(
	bigint,
	bigint,
	character varying,
	integer,
	character varying,
	character varying,
	character varying,
	character varying,
	character varying,
	character varying,
	character varying,
	character varying,
	character varying,
	character varying,
	character varying,
	character varying,
	character varying,
	character varying)
    RETURNS smallint
    LANGUAGE 'plpgsql'
    COST 100
    VOLATILE PARALLEL UNSAFE
AS $BODY$

DECLARE
	lNumEmpleado 			ALIAS FOR $1;
	lIDProyecto				ALIAS FOR $2;
	sProjectName			ALIAS FOR $3;
	iId						ALIAS FOR $4;
	dDetectionDate			ALIAS FOR $5;
	sDirectLink				ALIAS FOR $6;
	sQueryName				ALIAS FOR $7;
    sSourceFolder			ALIAS FOR $8;
	sSourceFilename			ALIAS FOR $9;
	sSourceLine				ALIAS FOR $10;
	sSourceObject			ALIAS FOR $11;
	sDestinationFolder		ALIAS FOR $12;
    sDestinationFilename	ALIAS FOR $13;
	sDestinationLine		ALIAS FOR $14;
	sDestinationObject		ALIAS FOR $15;
	sResultState			ALIAS FOR $16;
	sSeverity				ALIAS FOR $17;
    sResultSeverity			ALIAS FOR $18;
BEGIN	
	
	INSERT INTO public.tbl_registra_items_checkmarx( num_empleado, id_proyecto, nom_proyecto, num_id, fec_detection_date, rut_direct_link, fun_query_name, nom_source_folder, nom_source_filename, 
													 num_surce_line, nom_source_object, nom_destination_folder, nom_destination_filename, num_destination_line, nom_destination_object, nom_result_state, num_severity, nom_result_severity )
	VALUES ($1::bigint, $2::bigint, $3::varchar, $4::integer, $5::varchar, $6::varchar, $7::varchar, $8::varchar, $9::varchar, $10::varchar, $11::varchar, $12::varchar, $13::varchar, $14::varchar, $15::varchar, $16::varchar, $17::varchar, $18::varchar );
	
	RETURN 1; --Inserto
	
END
$BODY$;

------------------------------------------------------------------------------------------------------------------------------
-- FUNCTION: public.fun_registrar_obsoletos(bigint, bigint, character varying, character varying, integer, character varying)
-- DROP FUNCTION IF EXISTS public.fun_registrar_obsoletos(bigint, bigint, character varying, character varying, integer, character varying);

CREATE OR REPLACE FUNCTION public.fun_registrar_obsoletos(
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
	lIdProyecto		ALIAS FOR $2;
	sProyecto		ALIAS FOR $3;
	sArchivo		ALIAS FOR $4;
	iLinea			ALIAS FOR $5;
	sSentencia		ALIAS FOR $6;
BEGIN	
	
	INSERT INTO public.tbl_registra_obsoletos_ia( num_empleado, id_proyecto, nom_proyecto, nom_archivo, num_linea, dat_obsoleto )
	VALUES ($1::bigint, $2::bigint, $3::varchar, $4::varchar, $5::integer, $6::varchar);
	
	RETURN 1; --Inserto
	
END
$BODY$;

------------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------------
-- FUNCTION: public.fun_registrar_sentencias(bigint, bigint, character varying, character varying, integer, character varying)
-- DROP FUNCTION IF EXISTS public.fun_registrar_sentencias(bigint, bigint, character varying, character varying, integer, character varying);
-- SELECT fun_registrar_comentarios_proyecto_ia( '90329121'::BIGINT, '295202404'::BIGINT, 'Largo'::character varying, 'C:\Temp\Bito\Largo\function.counter.php'::character varying, 'CORRECTO'::character, 'Fri Apr  5 11:15:41 2024'::character, 'Fri Apr  5 11:16:12 2024'::character, '31.358349'::character, '0.522639'::character, 'CORRECTO'::character, 'No syntax errors detected in C:\Temp\Bito\Largo\function.counter.php'::character varying, 'Issues:-   Code formatting and style issues (1 point)  : The code lacks proper indentation and spacing which makes it difficult to read and maintain.-   Variable naming problems (1 point)  : The variable @$retval@ is not clearly named to describe its purpose.-   Comments and Documentation (2 points)  : While there is a significant amount of comments some parts of the code could benefit from more detailed explanations especially regarding the purpose and usage of the @$retval@ variable.-   Complex and illegible code (3 points)  : The logic for incrementing or decrementing the counter based on the @direction@ is embedded within the main function making the code harder to follow.-   Performance problems (4 points)  : The use of static variables and references (@&$counter@) may lead to unnecessary complexity and performance issues in certain contexts.-   Logic errors (4 points)  : The counter does not properly handle cases where @skip@ could be zero or negative potentially causing an infinite loop or logic error.Fixed code:- Improved variable naming and added more descriptive comments.- Added a check to ensure @skip@ is not zero to prevent potential infinite loops.- Reformatted the code for better readability and maintainability.'::character varying );

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

------------------------------------------------------------------------------------------------------------------------------
-- FUNCTION: public.fun_registrar_token(bigint, character varying, character varying)
-- DROP FUNCTION IF EXISTS public.fun_registrar_token(bigint, character varying, character varying);

CREATE OR REPLACE FUNCTION public.fun_registrar_token(
	bigint,
	character varying,
	timestamp)
    RETURNS smallint
    LANGUAGE 'plpgsql'
    COST 100
    VOLATILE PARALLEL UNSAFE
AS $BODY$

DECLARE
	lNumEmpleado 	ALIAS FOR $1;
	sToken			ALIAS FOR $2;
	sExpira			ALIAS FOR $3;
BEGIN	
	
	INSERT INTO public.ctl_token_ia( num_empleado, key_token, fec_expira )
	VALUES ($1::bigint, $2::varchar, $3::timestamp);
	
	RETURN 1; --Inserto
	
END
$BODY$;

------------------------------------------------------------------------------------------------------------------------------

-- FUNCTION: public.fun_registrar_totales_checkmarx(bigint, bigint, character varying, integer, integer, integer)
-- DROP FUNCTION IF EXISTS public.fun_registrar_totales_checkmarx(bigint, bigint, character varying, integer, integer, integer);

CREATE OR REPLACE FUNCTION public.fun_registrar_totales_checkmarx(
	bigint,
	bigint,
	character varying,
	integer,
	integer,
	integer)
    RETURNS smallint
    LANGUAGE 'plpgsql'
    COST 100
    VOLATILE PARALLEL UNSAFE
AS $BODY$

DECLARE
	lNumEmpleado	ALIAS FOR $1;
	lIDProyecto		ALIAS FOR $2;
	sNomProyecto	ALIAS FOR $3;
	iNumHigh		ALIAS FOR $4;
	iNumMedium		ALIAS FOR $5;
	iNumLow			ALIAS FOR $6;
BEGIN	
	
	INSERT INTO public.tbl_registra_totales_checkmarx( num_empleado, id_proyecto, nom_proyecto, num_high, num_medium, num_low )
	VALUES ($1::bigint, $2::bigint, $3::varchar, $4::integer, $5::integer, $6::integer);
	
	RETURN 1; --Inserto
	
END
$BODY$;

------------------------------------------------------------------------------------------------------------------------------
-- FUNCTION: public.fun_registrar_control_proyectos(bigint, bigint, character varying, integer)
-- DROP FUNCTION IF EXISTS public.fun_registrar_control_proyectos(bigint, bigint, character varying, integer);

CREATE OR REPLACE FUNCTION public.fun_registrar_control_proyectos(
	bigint,
	bigint,
	character varying,
	integer)
    
	RETURNS smallint
    LANGUAGE 'plpgsql'
    COST 100
    VOLATILE PARALLEL UNSAFE
AS $BODY$

DECLARE
	
	lEmpleado 		ALIAS FOR $1;
	lIdpproyecto 	ALIAS FOR $2;
	sNomProyecto 	ALIAS FOR $3;
	iFlgConIA		ALIAS FOR $4;
	
BEGIN	
		
	INSERT INTO public.ctl_proyectos( num_empleado, id_proyecto, nom_proyecto, flg_con_ia )
	VALUES ($1::bigint, $2::bigint, $3::varchar, $4::integer );
	
	RETURN 1; --Inserto
	
END
$BODY$;

------------------------------------------------------------------------------------------------------------------------------
-- FUNCTION: public.fun_registrar_totales_proyecto(bigint, bigint, character varying, character varying, integer, integer, integer, integer)
-- DROP FUNCTION IF EXISTS public.fun_registrar_totales_proyecto(bigint, bigint, character varying, character varying, integer, integer, integer, integer);

CREATE OR REPLACE FUNCTION public.fun_registrar_totales_proyecto(
	bigint,
	bigint,
	character varying,
	character varying,
	integer,
	integer,
	integer,
	integer)
    
	RETURNS smallint
    LANGUAGE 'plpgsql'
    COST 100
    VOLATILE PARALLEL UNSAFE
AS $BODY$

DECLARE
	
	lEmpleado 		ALIAS FOR $1;
	lIdpproyecto 	ALIAS FOR $2;
	sNomProyecto 	ALIAS FOR $3;
	sNomLenguaje 	ALIAS FOR $4;
	iNumFiles		ALIAS FOR $5;
	iNumBlank		ALIAS FOR $6;
	iNumComment		ALIAS FOR $7;
	iNumCode		ALIAS FOR $8;
	
BEGIN	
		
	INSERT INTO public.tbl_registra_totales( num_empleado, id_proyecto, nom_proyecto, nom_language, num_files, num_blank, num_comment, num_code )
	VALUES ($1::bigint, $2::bigint, $3::varchar, $4::varchar, $5::integer, $6::integer, $7::integer, $8::integer );
	
	RETURN 1; --Inserto
	
END
$BODY$;

------------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------------
-- FUNCTION: public.fun_validar_si_existe_colaborador(bigint)
-- DROP FUNCTION IF EXISTS public.fun_validar_si_existe_colaborador(bigint);

CREATE OR REPLACE FUNCTION public.fun_validar_si_existe_colaborador(
	bigint)
    RETURNS SETOF bigint 
    LANGUAGE 'plpgsql'
    COST 100
    VOLATILE PARALLEL UNSAFE
    ROWS 1000

AS $BODY$

DECLARE
	lNumero			ALIAS FOR $1;
BEGIN

	RETURN QUERY SELECT num_gerente FROM cat_gerentes WHERE num_gerente = $1::bigint;
	
	IF NOT FOUND THEN
	--	RAISE EXCEPTION 'No name at %.', $1;
		RETURN QUERY SELECT num_coordinador FROM cat_coordinadores WHERE num_coordinador = $1::bigint;
		
		IF NOT FOUND THEN
			
			RETURN QUERY SELECT num_nacional FROM cat_nacionales WHERE num_nacional = $1::bigint;	
			
			IF NOT FOUND THEN
				RETURN QUERY SELECT num_colaborador FROM cat_colaboradores WHERE num_colaborador = $1::bigint;	
			END IF;
		
		END IF;
		
	END IF;
	
	RETURN;
END
$BODY$;

------------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------------
-- FUNCTION: public.fun_registrar_comentarios_proyecto_ia(bigint, bigint, character varying, character varying, character, character, character, character, character, character, character varying, character varying)
-- DROP FUNCTION IF EXISTS public.fun_registrar_comentarios_proyecto_ia(bigint, bigint, character varying, character varying, character, character, character, character, character, character, character varying, character varying);
-- SELECT fun_registrar_comentarios_proyecto_ia( '90329121'::BIGINT, '35202404'::BIGINT, 'Largo'::character varying, 'C:\Temp\Bito\Largo\block.textformat.php'::character varying, 'CORRECTO'::character, 'Thu Apr  4 21:17:52 2024'::character, 'Thu Apr  4 21:18:32 2024'::character, '40.381697'::character, '0.673028'::character, 'CORRECTO'::character, 'No syntax errors detected in C:\Temp\Bito\Largo\block.textformat.php'::character varying, 'Issues:- **Comments and Documentation (2 points)**: The function documentation is comprehensive but the purpose of some parameters like `indent_first` `wrap_cut` and `assign` could be better explained in the context of their effect on the output.- **Complex and illegible code (3 points)**: The code has a high level of nesting and several operations within a single block making it difficult to read and maintain. Specifically the paragraph handling and word wrapping logic could be simplified or broken down into smaller functions.- **Performance problems (4 points)**: The repeated use of regular expressions and the handling of string operations in a loop can be inefficient especially for large blocks of text. The use of `preg_replace` in a loop for each paragraph could be optimized.- **Variable naming problems (1 point)**: Variable names like `$_key` `$_val` and `$_paragraphs` are not immediately clear and do not follow a clear naming convention that indicates their purpose or content.- **Logic errors (4 points)**: The check for `Smarty::$_MBSTRING` and the subsequent requirement of `smarty_mb_wordwrap.php` within the loop could lead to unnecessary overhead and potential errors if the file is missing or if `Smarty::$_MBSTRING` changes state during runtime.Fixed code:This revision aims to improve readability maintainability and performance by simplifying logic enhancing variable names and reducing unnecessary operations.'::character varying );
-- SELECT fun_registrar_comentarios_proyecto_ia( '90329121'::BIGINT, '638202404'::BIGINT, 'Largo'::character varying, 'C:\Temp\Bito\Largo\block.textformat.php'::character varying, 'CORRECTO'::character, 'Thu Apr  4 21:57:31 2024'::character, 'Thu Apr  4 21:58:13 2024'::character, '42.067853'::character, '0.701131'::character, 'CORRECTO'::character, 'No syntax errors detected in C:\Temp\Bito\Largo\block.textformat.php'::character varying, 'Issues:- **Security vulnerabilities (5 points)**: The function directly uses input parameters without sanitization or validation which could lead to security vulnerabilities such as XSS (Cross-Site Scripting) if the output is rendered in HTML without proper encoding.- **Performance problems (4 points)**: The function uses regular expressions and multiple `preg_replace` calls inside a loop. For large texts this could significantly impact performance. Additionally the use of `smarty_mb_wordwrap` (if `Smarty::$_MBSTRING` is true) in a loop can be inefficient for large texts due to the overhead of calling an external function repeatedly.- **Complex and illegible code (3 points)**: The function has a complex flow with nested conditions and loops making it difficult to understand and maintain. The mix of processing logic and configuration (e.g. `$style = 'email'`) within the same function adds to the complexity.- **Code Duplication (3 points)**: The pattern of replacing multiple spaces and trimming spaces is done using two separate `preg_replace` calls which could be combined or simplified to reduce redundancy and improve efficiency.- **Logic errors (4 points)**: The handling of the `$wrap` parameter changes based on the `$style` parameter being 'email' but this is hardcoded and not flexible for future styles that might also require different wrap values.- **Variable naming problems (1 point)**: The use of variable names like `$_key` `$_val` and `$_paragraph` is not clear and does not follow common naming conventions making the code harder to read and understand.Fixed code:- Improved variable naming for clarity.- Simplified and combined regex operations for efficiency.- Added comments for clarity and maintenance.- Ensured that the function is more readable and maintainable.'::character varying );


CREATE OR REPLACE FUNCTION public.fun_registrar_comentarios_proyecto_ia(
    bigint,
	bigint,
	character varying,
    character varying,
	character varying,
    character varying,
	character varying,
    character varying,
	character varying,
    character varying,
	character varying,
	TEXT)
    
	RETURNS smallint
    LANGUAGE 'plpgsql'
    COST 100
    VOLATILE PARALLEL UNSAFE
AS $BODY$

DECLARE
	
	lNumEmpleado 			ALIAS FOR $1;
	lIdProyecto 			ALIAS FOR $2;
	sNomProyecto 			ALIAS FOR $3;
    cArcProyecto 			ALIAS FOR $4;
	cLntAntes 				ALIAS FOR $5;
	cHraIniciaProyecto 		ALIAS FOR $6;
	cHraFinalizaProyecto 	ALIAS FOR $7;
	cTpoSegundos 			ALIAS FOR $8;
	cTpoMinutos 			ALIAS FOR $9;
	cLntDespues 			ALIAS FOR $10;
	cLntDescripcion 		ALIAS FOR $11;
	cComBito 				ALIAS FOR $12;

BEGIN	
	
	INSERT INTO public.tbl_registra_bito_ia( num_empleado, id_proyecto, nom_proyecto, arc_proyecto, lnt_antes, hra_inicia_proyecto, hra_finaliza_proyecto, tpo_segundos, tpo_minutos, lnt_despues, lnt_descripcion, com_bito )
	VALUES ($1::bigint, $2::bigint, $3::character varying, $4::character varying, $5::character varying, $6::character varying, $7::character varying, $8::character varying, $9::character varying, $10::character varying, $11::character varying, $12::TEXT );
	
	RETURN 1; --Inserto
	
END
$BODY$;
------------------------------------------------------------------------------------------------------------------------------