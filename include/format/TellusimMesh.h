// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#ifndef __TELLUSIM_FORMAT_MESH_H__
#define __TELLUSIM_FORMAT_MESH_H__

#include <TellusimFormat.h>
#include <math/TellusimMath.h>
#include <core/TellusimArray.h>
#include <core/TellusimString.h>
#include <geometry/TellusimBounds.h>

/*
 */
namespace Tellusim {
	
	/* Prototypes
	 */
	class Async;
	class Blob;
	class Image;
	class Stream;
	class MeshNode;
	class MeshJoint;
	class MeshIndices;
	class MeshAttribute;
	class MeshMaterial;
	class MeshGeometry;
	class MeshTransform;
	class MeshAnimation;
	class MeshAttachment;
	class Mesh;
	
	/**
	 * The MeshNode class represents a single node in a 3D mesh hierarchy and serves as a container for geometries, attachments, and transformation data.
	 * It supports hierarchical relationships by allowing parent-child connections between nodes, enabling complex scene graph structures.
	 * Each node can be associated with a mesh, named for identification, and optionally contain geometries.
	 */
	class TS_API MeshNode {
			
			friend class Mesh;
			
			TS_DECLARE_PTR(MeshNode, 0)
			
		public:
			
			explicit MeshNode(const char *name = nullptr);
			explicit MeshNode(Mesh &mesh, const char *name = nullptr);
			explicit MeshNode(MeshNode *parent, const char *name = nullptr);
			explicit MeshNode(Mesh &mesh, MeshNode *parent, const char *name = nullptr);
			
			/// clear node
			void clear();
			
			/// clone node
			MeshNode clone(Mesh &mesh) const;
			
			/// node name
			void setName(const char *name);
			String getName() const;
			
			/// node index
			uint32_t getIndex() const;
			
			/// node mesh
			void setMesh(Mesh &mesh, bool check = true);
			const Mesh getMesh() const;
			Mesh getMesh();
			
			/// node parent
			uint32_t setParent(MeshNode &parent, bool check = true);
			const MeshNode getParent() const;
			MeshNode getParent();
			
			bool isRoot() const;
			
			/// node children
			void reserveChildren(uint32_t num_children);
			uint32_t addChild(MeshNode &child, bool check = true);
			bool removeChild(MeshNode &child);
			void releaseChildren();
			
			uint32_t findChild(const MeshNode &child) const;
			uint32_t findChild(const char *name) const;
			
			uint32_t getNumChildren() const;
			const Array<MeshNode> getChildren() const;
			Array<MeshNode> getChildren();
			const MeshNode getChild(uint32_t index) const;
			const MeshNode getChild(const char *name) const;
			MeshNode getChild(uint32_t index);
			MeshNode getChild(const char *name);
			
			/// node geometries
			void clearGeometries();
			void reserveGeometries(uint32_t num_geometries);
			uint32_t addGeometry(MeshGeometry &geometry, bool check = true);
			bool removeGeometry(MeshGeometry &geometry);
			bool replaceGeometry(MeshGeometry &old_geometry, MeshGeometry &geometry);
			uint32_t findGeometry(const MeshGeometry &geometry) const;
			
			uint32_t getNumGeometries() const;
			const Array<MeshGeometry> getGeometries() const;
			Array<MeshGeometry> getGeometries();
			const MeshGeometry getGeometry(uint32_t index) const;
			MeshGeometry getGeometry(uint32_t index);
			
			/// node attachments
			void clearAttachments();
			void reserveAttachments(uint32_t num_attachments);
			uint32_t addAttachment(MeshAttachment &attachment, bool check = true);
			bool removeAttachment(MeshAttachment &attachment);
			bool replaceAttachment(MeshAttachment &old_attachment, MeshAttachment &attachment);
			uint32_t findAttachment(const MeshAttachment &attachment) const;
			uint32_t findAttachment(const char *name) const;
			
			uint32_t getNumAttachments() const;
			const Array<MeshAttachment> getAttachments() const;
			Array<MeshAttachment> getAttachments();
			const MeshAttachment getAttachment(uint32_t index) const;
			MeshAttachment getAttachment(uint32_t index);
			
			/// local transform
			void setLocalTransform(const Matrix4x3d &transform);
			const Matrix4x3d &getLocalTransform() const;
			
			/// global transform
			void setGlobalTransform(const Matrix4x3d &transform);
			const Matrix4x3d &getGlobalTransform() const;
			
			/// pivot transform
			void setPivotTransform(const Matrix4x3d &transform);
			const Matrix4x3d &getPivotTransform() const;
			
			/// morph transform
			void setMorphTransform(const Vector4f &transform);
			const Vector4f &getMorphTransform() const;
			
			/// create transforms
			void createLocalTransforms(const Matrix4x3d &itransform = Matrix4x3d::identity);
			void createGlobalTransforms(const Matrix4x3d &transform = Matrix4x3d::identity);
			
			/// apply transform
			void setTransform(const Vector3d &scale);
			
			/// memory usage
			size_t getMemory() const;
	};
	
	/**
	 * The MeshIndices class encapsulates index data used by mesh geometries to define how vertices are connected into primitives such as points, lines, triangles, and more complex topologies like quadrilaterals and tetrahedrons.
	 * Each MeshIndices instance has a specific type and format, allowing for flexible representation of both renderable geometry and auxiliary information like materials, groups, joints, and edges.
	 */
	class TS_API MeshIndices {
			
			friend class MeshGeometry;
			
			TS_DECLARE_PTR(MeshIndices, 0)
			
		public:
			
			/// Indices types
			enum Type {
				TypeUnknown = 0,
				TypePoint,			// point indices
				TypeLine,			// line indices
				TypeTriangle,		// triangle indices
				TypeQuadrilateral,	// quadrilateral indices
				TypeTetrahedron,	// tetrahedron indices
				TypeMaterial,		// material indices
				TypeIsland,			// island count indices
				TypeGroup,			// smooth mask indices
				TypeJoint,			// joint indices
				TypeEdge,			// edge indices
				NumTypes,
			};
			
			explicit MeshIndices(const char *name = nullptr);
			MeshIndices(Type type, Format format, const char *name = nullptr);
			MeshIndices(Type type, Format format, uint32_t size, const char *name = nullptr);
			
			/// clear indices
			void clear();
			
			/// indices name
			void setName(const char *name);
			String getName() const;
			
			/// create indices
			void create(Type type, Format format, uint32_t size = 0);
			
			/// indices type
			Type getType() const;
			
			static const char *getTypeName(Type type);
			const char *getTypeName() const;
			
			TS_INLINE bool isUnknown() const { return (getType() == TypeUnknown); }
			TS_INLINE bool isPoint() const { return (getType() == TypePoint); }
			TS_INLINE bool isLine() const { return (getType() == TypeLine); }
			TS_INLINE bool isTriangle() const { return (getType() == TypeTriangle); }
			TS_INLINE bool isQuadrilateral() const { return (getType() == TypeQuadrilateral); }
			TS_INLINE bool isTetrahedron() const { return (getType() == TypeTetrahedron); }
			TS_INLINE bool isPrimitive() const { return (getType() >= TypePoint && getType() <= TypeTetrahedron); }
			TS_INLINE bool isSolid() const { return (getType() >= TypeTriangle && getType() <= TypeQuadrilateral); }
			TS_INLINE bool isVolume() const { return (getType() == TypeTetrahedron); }
			TS_INLINE bool isMaterial() const { return (getType() == TypeMaterial); }
			TS_INLINE bool isGroup() const { return (getType() == TypeGroup); }
			TS_INLINE bool isJoint() const { return (getType() == TypeJoint); }
			TS_INLINE bool isEdge() const { return (getType() == TypeEdge); }
			
			uint32_t getPrimitiveSize() const;
			
			/// indices format
			Format getFormat() const;
			
			TS_INLINE const char *getFormatName() const { return Tellusim::getFormatName(getFormat()); }
			
			/// indices geometry
			void setGeometry(MeshGeometry &geometry, bool check = true);
			const MeshGeometry getGeometry() const;
			MeshGeometry getGeometry();
			
			/// indices size
			void setSize(uint32_t size, bool discard = true, bool clear = false);
			uint32_t getSize() const;
			uint32_t getStride() const;
			size_t getBytes() const;
			
			/// indices data
			void setData(uint32_t value, uint32_t size = 0, uint32_t offset = 0);
			void setData(const void *src, Format format = FormatUnknown, uint32_t size = 0, uint32_t repeat = 1);
			void getData(void *dest, Format format = FormatUnknown, uint32_t size = 0, uint32_t repeat = 1) const;
			const void *getData() const;
			void *getData();
			
			/// indices values
			void set(uint32_t index, uint32_t value);
			void set(uint32_t index, uint32_t value_0, uint32_t value_1);
			void set(uint32_t index, uint32_t value_0, uint32_t value_1, uint32_t value_2);
			void set(uint32_t index, uint32_t value_0, uint32_t value_1, uint32_t value_2, uint32_t value_3);
			
			uint32_t get(uint32_t index) const;
			void get(uint32_t index, uint32_t &value_0, uint32_t &value_1) const;
			void get(uint32_t index, uint32_t &value_0, uint32_t &value_1, uint32_t &value_2) const;
			void get(uint32_t index, uint32_t &value_0, uint32_t &value_1, uint32_t &value_2, uint32_t &value_3) const;
			
			/// indices pointers
			const void *getPtr(uint32_t index) const;
			void *getPtr(uint32_t index);
			
			/// direct indices flag
			bool isDirect() const;
			
			/// uniform indices flag
			bool isUniform() const;
			
			/// indices range
			uint32_t getMinIndex() const;
			uint32_t getMaxIndex() const;
			
			/// compare indices
			int32_t compare(const MeshIndices &indices) const;
			
			/// add indices
			void addIndices(const MeshIndices &indices, uint32_t offset, bool expand = false);
			
			/// convert indices to format
			MeshIndices toFormat(Format format) const;
			
			/// convert indices to type
			MeshIndices toType(Type type) const;
			MeshIndices toType(Type type, const MeshAttribute &position_attribute) const;
			
			/// memory usage
			size_t getMemory() const;
	};
	
	/**
	 * The MeshAttribute class represents per-vertex attribute data in a mesh, such as positions, normals, texture coordinates, colors, and joint weights.
	 * Each attribute has a type, format, name, index (used for distinguishing between multiple attributes of the same type), and size.
	 * The class allows setting and retrieving attribute values, either directly or via associated index data (MeshIndices), and supports various utilities for transformation, morphing, packing/unpacking, and optimization.
	 */
	class TS_API MeshAttribute {
			
			friend class MeshGeometry;
			
			TS_DECLARE_PTR(MeshAttribute, 0)
			
		public:
			
			/// Attribute types
			enum Type {
				TypeUnknown = 0,
				TypePosition,		// position attribute
				TypeBasis,			// basis attribute
				TypeNormal,			// normal attribute
				TypeTangent,		// tangent attribute
				TypeBinormal,		// binormal attribute
				TypeTexCoord,		// texcoord attribute
				TypeWeights,		// weights attribute
				TypeJoints,			// joints attribute
				TypeColor,			// color attribute
				TypeCrease,			// crease attribute
				TypeIndex,			// index attribute
				NumTypes,
			};
			
			explicit MeshAttribute(const char *name = nullptr, uint32_t index = 0);
			MeshAttribute(Type type, Format format, const char *name = nullptr, uint32_t index = 0);
			MeshAttribute(Type type, Format format, uint32_t size, const char *name = nullptr, uint32_t index = 0);
			MeshAttribute(Type type, Format format, uint32_t size, uint32_t index);
			
			/// clear attributes
			void clear();
			
			/// attribute name
			void setName(const char *name);
			String getName() const;
			
			/// create attribute
			void create(Type type, Format format, uint32_t size = 0);
			
			/// attribute type
			Type getType() const;
			
			static const char *getTypeName(Type type);
			const char *getTypeName() const;
			
			TS_INLINE bool isUnknown() const { return (getType() == TypeUnknown); }
			TS_INLINE bool isPosition() const { return (getType() == TypePosition); }
			TS_INLINE bool isBasis() const { return (getType() == TypeBasis); }
			TS_INLINE bool isNormal() const { return (getType() == TypeNormal); }
			TS_INLINE bool isTangent() const { return (getType() == TypeTangent); }
			TS_INLINE bool isBinormal() const { return (getType() == TypeBinormal); }
			TS_INLINE bool isSpatial() const { return (getType() >= TypePosition && getType() <= TypeBinormal); }
			TS_INLINE bool isNormalized() const { return (getType() >= TypeBasis && getType() <= TypeBinormal); }
			TS_INLINE bool isTexCoord() const { return (getType() == TypeTexCoord); }
			TS_INLINE bool isWeights() const { return (getType() == TypeWeights); }
			TS_INLINE bool isJoints() const { return (getType() == TypeJoints); }
			TS_INLINE bool isColor() const { return (getType() == TypeColor); }
			TS_INLINE bool isVertex() const { return (getType() >= TypePosition && getType() <= TypeColor); }
			TS_INLINE bool isCrease() const { return (getType() == TypeCrease); }
			
			/// attribute format
			Format getFormat() const;
			
			TS_INLINE const char *getFormatName() const { return Tellusim::getFormatName(getFormat()); }
			
			TS_INLINE uint32_t getComponents() const { return getFormatComponents(getFormat()); }
			
			bool isPacked() const;
			
			/// attribute index
			void setIndex(uint32_t index);
			uint32_t getIndex() const;
			
			/// attribute indices
			void setIndices(MeshIndices &indices);
			const MeshIndices getIndices() const;
			MeshIndices getIndices();
			
			/// attribute geometry
			void setGeometry(MeshGeometry &geometry, bool check = true);
			const MeshGeometry getGeometry() const;
			MeshGeometry getGeometry();
			
			/// attribute size
			void setSize(uint32_t size, bool discard = true, bool clear = false);
			uint32_t getSize() const;
			uint32_t getStride() const;
			size_t getBytes() const;
			
			/// attribute data
			void setData(const void *src, uint32_t size = 0, uint32_t stride = 0);
			void setData(const void *src, const Array<uint32_t> &indices, uint32_t stride = 0);
			void getData(void *dest, uint32_t size = 0, uint32_t stride = 0) const;
			void getData(void *dest, const MeshIndices &indices, uint32_t stride = 0) const;
			void getData(void *dest, const Array<uint32_t> &indices, uint32_t stride = 0) const;
			const void *getData() const;
			void *getData();
			
			/// attribute values
			template <class Type> void set(const Type &value) {
				TS_ASSERT(sizeof(Type) <= getStride() && "MeshAttribute::set(): invalid type");
				setData(&value);
			}
			template <class Type> void set(uint32_t index, const Type &value) {
				TS_ASSERT(index < getSize() && "MeshAttribute::set(): invalid index");
				TS_ASSERT(sizeof(Type) <= getStride() && "MeshAttribute::set(): invalid type");
				*((Type*)((uint8_t*)getData() + (size_t)getStride() * index)) = value;
			}
			template <class Type> const Type &get(uint32_t index) const {
				TS_ASSERT(index < getSize() && "MeshAttribute::get(): invalid index");
				TS_ASSERT(sizeof(Type) <= getStride() && "MeshAttribute::get(): invalid type");
				return *((const Type*)((const uint8_t*)getData() + (size_t)getStride() * index));
			}
			template <class Type> Type &get(uint32_t index) {
				TS_ASSERT(index < getSize() && "MeshAttribute::get(): invalid index");
				TS_ASSERT(sizeof(Type) <= getStride() && "MeshAttribute::get(): invalid type");
				return *((Type*)((const uint8_t*)getData() + (size_t)getStride() * index));
			}
			
			/// attribute value
			void setValue(uint32_t index, const void *src, size_t size);
			void getValue(uint32_t index, void *dest, size_t size) const;
			
			/// attribute pointers
			const void *getPtr(uint32_t index) const;
			void *getPtr(uint32_t index);
			
			/// compare attributes
			int32_t compare(const MeshAttribute &attribute, const Matrix4x3f &transform = Matrix4x3f::identity, float32_t threshold = 1e-6f, bool spatial = true) const;
			
			/// add attribute
			void addAttribute(const MeshAttribute &attribute);
			
			/// apply transform
			bool setTransform(const Vector3f &scale);
			bool setTransform(const Matrix4x3f &transform);
			
			/// morph attribute
			bool morphAttribute(const MeshAttribute &attribute, float32_t k);
			
			/// pack attributes
			bool packAttributes(const MeshAttribute &attribute_0, const MeshAttribute &attribute_1, Format format);
			bool unpackAttributes(MeshAttribute &attribute_0, MeshAttribute &attribute_1) const;
			
			/// optimize attribute by removing duplicates
			MeshAttribute optimizeAttribute(MeshIndices &indices) const;
			
			/// convert attribute to direct
			MeshAttribute toDirect(const MeshIndices &indices) const;
			
			/// convert attribute to format
			MeshAttribute toFormat(Format format) const;
			
			/// convert attribute to type
			MeshAttribute toType(Type type) const;
			
			/// covariance matrix
			Matrix4x3f getCovarianceMatrix() const;
			
			/// minimal bound transform
			Matrix4x3f getMinTransform() const;
			
			/// attribute bound box
			BoundBoxf getBoundBox() const;
			
			/// attribute bound sphere
			BoundSpheref getBoundSphere() const;
			
			/// memory usage
			size_t getMemory() const;
	};
	
	/**
	 * The MeshJoint class represents a skeletal joint within a mesh geometry, used for skeletal animation and skinning.
	 * It encapsulates joint metadata, including its name, associated node, transformation matrices (local/global), inverse bind transform, and optional bounding volumes.
	 */
	class TS_API MeshJoint {
			
			friend class MeshGeometry;
			
			TS_DECLARE_PTR(MeshJoint, 0)
			
		public:
			
			explicit MeshJoint(const char *name = nullptr);
			explicit MeshJoint(MeshGeometry &geometry, const char *name = nullptr);
			
			/// clear joint
			void clear();
			
			/// joint name
			void setName(const char *name);
			String getName() const;
			
			/// joint node
			void setNode(MeshNode &node);
			const MeshNode getNode() const;
			MeshNode getNode();
			
			uint32_t getNodeIndex() const;
			
			const Matrix4x3d &getLocalTransform() const;
			const Matrix4x3d &getGlobalTransform() const;
			
			/// joint indices
			void setIndices(MeshIndices &indices);
			const MeshIndices getIndices() const;
			MeshIndices getIndices();
			
			/// joint geometry
			void setGeometry(MeshGeometry &geometry, bool check = true);
			const MeshGeometry getGeometry() const;
			MeshGeometry getGeometry();
			
			/// joint bound box
			void setBoundBox(const BoundBoxf &box);
			const BoundBoxf &getBoundBox() const;
			
			/// joint bound sphere
			void setBoundSphere(const BoundSpheref &sphere);
			const BoundSpheref &getBoundSphere();
			
			/// inverse joint transform
			void setITransform(const Matrix4x3f &itransform);
			const Matrix4x3f &getITransform() const;
			
			/// compare joints
			int32_t compare(const MeshJoint &joint) const;
			
			/// memory usage
			size_t getMemory() const;
	};
	
	/**
	 * The MeshMaterial class represents a material used in a MeshGeometry object, supporting a flexible system of parameters for defining surface properties such as textures, colors, scalars, vectors, and transformation matrices.
	 * Materials can be named, assigned to geometries, and include multiple parameters identified by type strings.
	 * These parameters can store booleans, floats, vectors, matrices, colors, strings, images, and binary blobs.
	 */
	class TS_API MeshMaterial {
			
			friend class MeshGeometry;
			
			TS_DECLARE_PTR(MeshMaterial, 0)
			
		public:
			
			/// Material flags
			enum Flags {
				FlagNone = 0,
				FlagBool		= (1 << 0),		// boolean parameter flag
				FlagScalarf32	= (1 << 1),		// scalar parameter flag
				FlagVector4f	= (1 << 2),		// vector parameter flag
				FlagMatrix3x2f	= (1 << 3),		// matrix parameter flag
				FlagColor		= (1 << 4),		// color parameter flag
				FlagName		= (1 << 5),		// name parameter flag
				FlagLayout		= (1 << 6),		// layout parameter flag
				FlagBlob		= (1 << 7),		// blob parameter flag
				FlagImage		= (1 << 8),		// image parameter flag
				FlagTexture		= (FlagName | FlagBlob | FlagImage),
			};
			
			explicit MeshMaterial(const char *name = nullptr);
			explicit MeshMaterial(MeshGeometry &geometry, const char *name = nullptr);
			
			/// clear material
			void clear();
			
			/// material name
			void setName(const char *name);
			String getName() const;
			
			/// material index
			uint32_t getIndex() const;
			
			/// material indices
			void setIndices(MeshIndices &indices);
			const MeshIndices getIndices() const;
			MeshIndices getIndices();
			
			/// material geometry
			void setGeometry(MeshGeometry &geometry, bool check = true);
			const MeshGeometry getGeometry() const;
			MeshGeometry getGeometry();
			
			/// material data
			void setData(const char *data);
			void setData(const String &data);
			String getData() const;
			
			/// material parameters
			void clearParameters();
			bool removeParameter(const char *type);
			void copyParameters(const MeshMaterial &material);
			uint32_t findParameter(const char *type) const;
			bool hasParameter(const char *type) const;
			
			uint32_t getNumParameters() const;
			String getParameterType(uint32_t index) const;
			
			/// add material parameters
			void addParameter(const char *type, bool value);
			void addParameter(const char *type, float32_t value);
			void addParameter(const char *type, const Vector4f &value);
			void addParameter(const char *type, const Matrix3x2f &value);
			void addParameter(const char *type, const Color &color);
			
			void addParameter(const char *type, const char *name, const char *layout = nullptr);
			void addParameter(const char *type, const String &name, const char *layout = nullptr);
			void addParameter(const char *type, const Image &image, const char *layout = nullptr);
			void addParameter(const char *type, Blob &blob, const char *layout = nullptr);
			
			/// get material parameter by index
			Flags getParameterFlags(uint32_t index) const;
			bool hasParameterFlag(uint32_t index, Flags flags) const;
			bool hasParameterFlags(uint32_t index, Flags flags) const;
			
			bool getParameterBool(uint32_t index, bool value = false) const;
			float32_t getParameterScalarf32(uint32_t index, float32_t value = 0.0f) const;
			const Vector4f &getParameterVector4f(uint32_t index, const Vector4f &vector = Vector4f::zero) const;
			const Matrix3x2f &getParameterMatrix3x2f(uint32_t index, const Matrix3x2f &matrix = Matrix3x2f::identity) const;
			const Color &getParameterColor(uint32_t index, const Color &color = Color::white) const;
			String getParameterName(uint32_t index, const String &name = String::null) const;
			String getParameterLayout(uint32_t index, const String &layout = String::null) const;
			const Image getParameterImage(uint32_t index) const;
			Blob getParameterBlob(uint32_t index) const;
			Image getParameterImage(uint32_t index);
			Blob getParameterBlob(uint32_t index);
			
			/// get material parameter by type
			Flags getParameterFlags(const char *type) const;
			bool hasParameterFlag(const char *type, Flags flags) const;
			bool hasParameterFlags(const char *type, Flags flags) const;
			
			bool getParameterBool(const char *type, bool value = false) const;
			float32_t getParameterScalarf32(const char *type, float32_t value = 0.0f) const;
			const Vector4f &getParameterVector4f(const char *type, const Vector4f &vector = Vector4f::zero) const;
			const Matrix3x2f &getParameterMatrix3x2f(const char *type, const Matrix3x2f &matrix = Matrix3x2f::identity) const;
			const Color &getParameterColor(const char *type, const Color &color = Color::white) const;
			String getParameterName(const char *type, const String &name = String::null) const;
			String getParameterLayout(const char *type, const String &layout = String::null) const;
			
			/// compare materials
			int32_t compare(const MeshMaterial &material) const;
			
			/// memory usage
			size_t getMemory() const;
			
			/// parameter types
			static const char *TypeBump;
			static const char *TypeHeight;
			static const char *TypeNormal;
			static const char *TypeEmission;
			static const char *TypeOcclusion;
			static const char *TypeOpacity;
			static const char *TypeAmbient;
			static const char *TypeDiffuse;
			static const char *TypeSpecular;
			static const char *TypeMetallic;
			static const char *TypeRoughness;
			static const char *TypeShininess;
			static const char *TypeGlossiness;
			static const char *TypeTransparent;
			static const char *TypeTransparency;
			static const char *TypeTransmission;
			static const char *TypeReflective;
			static const char *TypeReflectivity;
			static const char *TypeRefractiveIndex;
			static const char *TypeClearcoat;
			static const char *TypeClearcoatNormal;
			static const char *TypeClearcoatRoughness;
			static const char *TypeClearcoatGlossiness;
			static const char *TypeIridescence;
			static const char *TypeIridescenceThickness;
			static const char *TypeIridescenceRefractiveIndex;
			static const char *TypeSheen;
			static const char *TypeSheenRoughness;
			static const char *TypeVolume;
			static const char *TypeVolumeThickness;
			static const char *TypeAnisotropy;
			static const char *TypeAnisotropyAngle;
			static const char *TypeDoubleSided;
			static const char *TypeAlphaBlend;
			static const char *TypeAlphaMask;
			static const char *TypeTechnique;
			static const char *TypeTexCoord;
	};
	
	/**
	 * The MeshGeometry class represents the geometric structure of a 3D mesh, including its vertices, indices, attributes, joints, and materials.
	 * It allows for defining and manipulating the geometry hierarchical relationships, such as setting parent-child relationships between geometries, with support for two parent geometries to create seamless Level of Detail (LOD) transitions.
	 * This structure facilitates smooth blending of multiple geometric details based on distance or camera view, ensuring efficient rendering by dynamically adjusting the complexity of the mesh.
	 * The class provides methods for managing attributes like positions, normals, tangents, and texcoords, along with supporting operations for creating normals, tangents, and tangent basis.
	 * It also includes functionality for creating, optimizing, and managing materials, bounds, and visibility ranges.
	 */
	class TS_API MeshGeometry {
			
			friend class Mesh;
			
			TS_DECLARE_PTR(MeshGeometry, 0)
			
		public:
			
			explicit MeshGeometry(const char *name = nullptr);
			explicit MeshGeometry(Mesh &mesh, const char *name = nullptr);
			
			/// clear geometry
			void clear();
			
			/// geometry name
			void setName(const char *name);
			String getName() const;
			
			/// geometry index
			uint32_t getIndex() const;
			
			/// geometry mesh
			void setMesh(Mesh &mesh, bool check = true);
			const Mesh getMesh() const;
			Mesh getMesh();
			
			/// geometry parent
			uint32_t setParent0(MeshGeometry &parent, bool check = true);
			uint32_t setParent1(MeshGeometry &parent, bool check = true);
			const MeshGeometry getParent0() const;
			const MeshGeometry getParent1() const;
			MeshGeometry getParent0();
			MeshGeometry getParent1();
			
			bool isRoot() const;
			
			/// geometry children
			void reserveChildren(uint32_t num_children);
			uint32_t addChild0(MeshGeometry &child, bool check = true);
			uint32_t addChild1(MeshGeometry &child, bool check = true);
			bool removeChild(MeshGeometry &child);
			void releaseChildren();
			
			uint32_t findChild(const MeshGeometry &child) const;
			
			uint32_t getNumChildren() const;
			const Array<MeshGeometry> getChildren() const;
			Array<MeshGeometry> getChildren();
			const MeshGeometry getChild(uint32_t index) const;
			MeshGeometry getChild(uint32_t index);
			
			/// geometry indices
			void clearIndices();
			void reserveIndices(uint32_t num_indices);
			uint32_t addIndices(MeshIndices &indices, bool check = true);
			bool removeIndices(MeshIndices &indices);
			bool replaceIndices(MeshIndices &old_indices, MeshIndices &indices);
			uint32_t findIndices(const MeshIndices &indices) const;
			uint32_t findIndices(MeshIndices::Type type) const;
			bool hasIndices(MeshIndices::Type type) const;
			bool hasSolidIndices() const;
			
			uint32_t getNumIndices(MeshIndices::Type type) const;
			const MeshIndices getIndices(MeshIndices::Type type) const;
			MeshIndices getIndices(MeshIndices::Type type);
			
			uint32_t getNumIndices() const;
			const Array<MeshIndices> getIndices() const;
			Array<MeshIndices> getIndices();
			const MeshIndices getIndices(uint32_t index) const;
			MeshIndices getIndices(uint32_t index);
			
			/// geometry attributes
			void clearAttributes();
			void reserveAttributes(uint32_t num_attributes);
			uint32_t addAttribute(MeshAttribute &attribute, bool check = true);
			uint32_t addAttribute(MeshAttribute &attribute, MeshIndices &indices, bool check = true);
			bool removeAttribute(MeshAttribute &attribute);
			bool replaceAttribute(MeshAttribute &old_attribute, MeshAttribute &attribute);
			bool replaceAttributeIndices(const MeshIndices &old_indices, MeshIndices &indices);
			uint32_t findAttribute(MeshAttribute::Type type, Format format, uint32_t index = 0) const;
			uint32_t findAttribute(MeshAttribute::Type type, uint32_t index = 0) const;
			uint32_t findAttribute(const char *name, uint32_t index = 0) const;
			uint32_t findAttribute(const MeshAttribute &attribute) const;
			bool hasAttribute(MeshAttribute::Type type, Format format, uint32_t index = 0) const;
			bool hasAttribute(MeshAttribute::Type type, uint32_t index = 0) const;
			bool hasAttribute(const char *name, uint32_t index = 0) const;
			bool hasAttribute(const MeshAttribute &attribute) const;
			
			uint32_t getNumAttributes(MeshAttribute::Type type) const;
			uint32_t getNumAttributes(const MeshIndices &indices) const;
			const MeshAttribute getAttribute(MeshAttribute::Type type, uint32_t index = 0) const;
			MeshAttribute getAttribute(MeshAttribute::Type type, uint32_t index = 0);
			
			uint32_t getNumAttributes() const;
			const Array<MeshAttribute> getAttributes() const;
			Array<MeshAttribute> getAttributes();
			const MeshAttribute getAttribute(uint32_t index) const;
			MeshAttribute getAttribute(uint32_t index);
			
			/// geometry joints
			void clearJoints();
			void reserveJoints(uint32_t num_joints);
			uint32_t addJoint(MeshJoint &joint, bool check = true);
			uint32_t addJoint(MeshJoint &joint, MeshNode &node, bool check = true);
			bool removeJoint(MeshJoint &joint);
			bool replaceJoint(MeshJoint &old_joint, MeshJoint &joint);
			uint32_t findJoint(const MeshJoint &joint) const;
			uint32_t findJoint(const MeshNode &node) const;
			uint32_t findJoint(const char *name) const;
			
			uint32_t getNumJoints() const;
			const Array<MeshJoint> getJoints() const;
			Array<MeshJoint> getJoints();
			const MeshJoint getJoint(uint32_t index) const;
			MeshJoint getJoint(uint32_t index);
			
			/// geometry materials
			void clearMaterials();
			void reserveMaterials(uint32_t num_materials);
			uint32_t addMaterial(MeshMaterial &material, bool check = true);
			uint32_t addMaterial(MeshMaterial &material, MeshIndices &indices, bool check = true);
			bool removeMaterial(MeshMaterial &material);
			bool replaceMaterial(MeshMaterial &old_material, MeshMaterial &material);
			uint32_t findMaterial(const MeshMaterial &material) const;
			uint32_t findMaterial(const char *name) const;
			
			uint32_t getNumMaterials() const;
			const Array<MeshMaterial> getMaterials() const;
			Array<MeshMaterial> getMaterials();
			const MeshMaterial getMaterial(uint32_t index) const;
			MeshMaterial getMaterial(uint32_t index);
			
			/// geometry bound box
			void setBoundBox(const BoundBoxf &box);
			const BoundBoxf &getBoundBox() const;
			
			/// geometry bound sphere
			void setBoundSphere(const BoundSpheref &sphere);
			const BoundSpheref &getBoundSphere() const;
			
			/// geometry transform
			bool setTransform(const Vector3f &scale);
			bool setTransform(const Matrix4x3f &transform, bool apply = false);
			const Matrix4x3f &getTransform() const;
			
			/// geometry inverse joint transform
			void setJointITransform(const Matrix4x3f &itransform);
			const Matrix4x3f &getJointITransform() const;
			
			/// visibility range
			void setMinVisibility(float32_t distance);
			void setMaxVisibility(float32_t distance);
			void setVisibilityRange(float32_t min, float32_t max);
			float32_t getMinVisibility() const;
			float32_t getMaxVisibility() const;
			bool hasVisibilityRange() const;
			
			/// visibility error
			void setVisibilityError(float32_t error);
			float32_t getVisibilityError() const;
			
			/// flip indices winding
			void flipWinding();
			
			/// create bounds
			/// \param force Force bounding creation.
			/// \param position Position attribute index.
			bool createBounds(bool force = false, uint32_t position = Maxu32);
			
			/// create tangent basis
			/// \param force Force basis creation.
			/// \param position Position attribute index.
			/// \param normal Normal attribute index.
			/// \param tangent Tangent attribute index.
			/// \param append Append new basis attribute.
			/// \return Basis attribute index.
			uint32_t createBasis(bool force = false, uint32_t position = Maxu32, uint32_t normal = Maxu32, uint32_t tangent = Maxu32, bool append = false);
			uint32_t createBasis(float32_t angle, bool force = false, uint32_t position = Maxu32, uint32_t normal = Maxu32, uint32_t tangent = Maxu32, bool append = false);
			
			/// create normals
			/// \param force Force normals creation.
			/// \param position Position attribute index.
			/// \param angle Smoothing angle in degrees.
			/// \param append Append new normal attribute.
			/// \return Normal attribute index.
			uint32_t createNormals(bool force = false, uint32_t position = Maxu32, bool append = false);
			uint32_t createNormals(float32_t angle, bool force = false, uint32_t position = Maxu32, bool append = false);
			
			/// create tangents
			/// \param force Force tangents creation.
			/// \param position Position attribute index.
			/// \param normal Normal attribute index.
			/// \param texcoord TexCoord attribute index.
			/// \param append Append new tangent attribute.
			/// \return Tangent attribute index.
			uint32_t createTangents(bool force = false, uint32_t position = Maxu32, uint32_t normal = Maxu32, uint32_t texcoord = Maxu32, bool append = false);
			
			/// create islands
			/// \param max_attributes Maximum number of attributes per island.
			/// \param max_primitives Maximum number of primitives per island.
			/// \param index Indices index to update.
			/// \param position Position attribute index.
			/// \param append Append new island indices.
			/// \return Island indices index.
			uint32_t createIslands(uint32_t max_attributes, uint32_t max_primitives, bool force = false, uint32_t index = Maxu32, uint32_t position = Maxu32, bool append = false);
			
			/// optimize indices
			/// \param cache Vertex cache size.
			/// \param transparent Optimize for transparency.
			/// \param index Indices index to optimize.
			/// \param position Position attribute index.
			bool optimizeIndices(uint32_t cache = 32, bool transparent = false, uint32_t index = Maxu32, uint32_t position = Maxu32);
			
			/// optimize attributes and make single indices.
			/// \param material material index.
			bool optimizeAttributes(uint32_t material = Maxu32);
			
			/// optimize materials remove duplicates
			void optimizeMaterials();
			
			/// optimize attribute and indices order
			void optimizeOrder();
			
			/// pack attributes (morph targets, texture coordinates and vertex colors)
			bool packAttributes(bool remove = true);
			bool unpackAttributes(bool remove = true);
			
			/// add geometry
			bool addGeometry(const MeshGeometry &geometry, const Matrix4x3f &transform = Matrix4x3f::identity);
			
			/// compare geometries
			int32_t compare(const MeshGeometry &geometry, const Matrix4x3f &transform = Matrix4x3f::identity, float32_t threshold = 1e-6f, bool spatial = true) const;
			
			/// optimized geometry flag (if geometry contains single indices).
			bool isOptimized() const;
			
			/// validate geometry
			bool validate() const;
			
			/// memory usage
			size_t getMemory() const;
	};
	
	/**
	 * The MeshTransform class provides functionality for defining and manipulating transformations applied to a 3D mesh over time.
	 * It supports transformations such as translation, rotation, scale, and morphing, allowing each transformation to be set and retrieved for specific time intervals.
	 * The class includes methods for managing keyframes for each type of transformation, enabling smooth animation and interpolation of transformations between time points.
	 */
	class TS_API MeshTransform {
			
			TS_DECLARE_PTR(MeshTransform, 0)
			
		public:
			
			MeshTransform();
			
			/// clear transform
			void clear();
			
			/// time range
			float64_t getMinTime() const;
			float64_t getMaxTime() const;
			
			/// set transform
			void setTransform(float64_t time, const Matrix4x3d &transform, float32_t threshold = 1e-6f);
			void setTranslate(float64_t time, const Vector3d &translate, float32_t threshold = 1e-6f);
			void setRotate(float64_t time, const Quaternionf &rotate, float32_t threshold = 1e-6f);
			void setScale(float64_t time, const Vector3f &scale, float32_t threshold = 1e-6f);
			void setMorph(float64_t time, const Vector4f &morph, float32_t threshold = 1e-6f);
			
			/// get transform
			Matrix4x3d getTransform(float64_t time) const;
			Vector3d getTranslate(float64_t time) const;
			Quaternionf getRotate(float64_t time) const;
			Vector3f getScale(float64_t time) const;
			Vector4f getMorph(float64_t time) const;
			
			/// transform data
			template <class Type> struct KeyData {
				float64_t time;
				Type data;
			};
			
			/// transform keys
			bool hasTransformKeys() const;
			
			/// translation keys
			using TranslateKeys = Array<KeyData<Vector3d>>;
			void setTranslateKeys(const TranslateKeys &keys, float64_t scale = 1.0);
			TranslateKeys getTranslateKeys() const;
			bool hasTranslateKeys() const;
			
			/// rotation keys
			using RotateKeys = Array<KeyData<Quaternionf>>;
			void setRotateKeys(const RotateKeys &keys);
			RotateKeys getRotateKeys() const;
			bool hasRotateKeys() const;
			
			/// scaling keys
			using ScaleKeys = Array<KeyData<Vector3f>>;
			void setScaleKeys(const ScaleKeys &keys);
			ScaleKeys getScaleKeys() const;
			bool hasScaleKeys() const;
			
			/// morphing keys
			using MorphKeys = Array<KeyData<Vector4f>>;
			void setMorphKeys(const MorphKeys &keys);
			MorphKeys getMorphKeys() const;
			bool hasMorphKeys() const;
			
			/// apply transform
			void setTransform(const Vector3d &scale);
			void setTransform(const Matrix4x3d &transform);
			
			/// memory usage
			size_t getMemory() const;
	};
	
	/**
	 * The MeshAnimation class represents a collection of transformations applied to a mesh over time, typically used to animate 3D models.
	 * It allows for managing and retrieving a series of transformations for multiple nodes or joints within the mesh.
	 * The class provides methods to set and retrieve transformations at specific time intervals, including translation, rotation, scale, and morphing.
	 * It also supports optimization of transforms and the calculation of bounding boxes for the animated mesh.
	 * The MeshAnimation class is designed to efficiently handle complex animations, including looping and applying transformations across multiple mesh nodes or joints.
	 */
	class TS_API MeshAnimation {
			
			friend class Mesh;
			
			TS_DECLARE_PTR(MeshAnimation, 0)
			
		public:
			
			explicit MeshAnimation(const char *name = nullptr);
			explicit MeshAnimation(Mesh &mesh, const char *name = nullptr);
			
			/// clear animation
			void clear();
			
			/// animation index
			uint32_t getIndex() const;
			
			/// animation name
			void setName(const char *name);
			String getName() const;
			
			/// animation mesh
			void setMesh(Mesh &mesh, bool check = true);
			const Mesh getMesh() const;
			Mesh getMesh();
			
			/// animation range
			float64_t getMinTime() const;
			float64_t getMaxTime() const;
			
			/// animation transforms
			void setNumTransforms(uint32_t num_transforms);
			
			uint32_t getNumTransforms() const;
			const Array<MeshTransform> getTransforms() const;
			Array<MeshTransform> getTransforms();
			const MeshTransform getTransform(uint32_t node) const;
			MeshTransform getTransform(uint32_t node);
			
			void setTransform(float64_t time, uint32_t node, const Matrix4x3d &transform, float32_t threshold = 1e-6f);
			void setTranslate(float64_t time, uint32_t node, const Vector3d &translate, float32_t threshold = 1e-6f);
			void setRotate(float64_t time, uint32_t node, const Quaternionf &rotate, float32_t threshold = 1e-6f);
			void setScale(float64_t time, uint32_t node, const Vector3f &scale, float32_t threshold = 1e-6f);
			void setMorph(float64_t time, uint32_t node, const Vector4f &morph, float32_t threshold = 1e-6f);
			
			/// animation transform
			void setTime(float64_t time, const Matrix4x3d &transform = Matrix4x3d::identity, bool loop = true, float64_t from = -Maxf32, float64_t to = Maxf32);
			void setTime(float64_t time, bool loop, float64_t from = -Maxf32, float64_t to = Maxf32) { setTime(time, Matrix4x3d::identity, loop, from, to); }
			
			const Matrix4x3d &getLocalTransform(uint32_t node) const;
			const Matrix4x3d &getLocalTransform(const MeshNode &node) const;
			const Matrix4x3d &getLocalTransform(const MeshJoint &joint) const;
			
			const Matrix4x3d &getGlobalTransform(uint32_t node) const;
			const Matrix4x3d &getGlobalTransform(const MeshNode &node) const;
			const Matrix4x3d &getGlobalTransform(const MeshJoint &joint) const;
			
			const Vector4f &getMorphTransform(uint32_t node) const;
			const Vector4f &getMorphTransform(const MeshNode &node) const;
			
			/// animation bound box
			BoundBoxd getBoundBox() const;
			BoundBoxd getBoundBox(const MeshNode &node) const;
			BoundBoxd getBoundBox(const MeshGeometry &geometry) const;
			BoundBoxd getBoundBox(const MeshGeometry &geometry, const Vector4f &morph) const;
			
			/// apply transform
			void setTransform(const Vector3d &scale);
			void setTransform(const Matrix4x3d &transform);
			
			/// optimize animation
			void optimizeTransforms(float32_t threshold = 1e-6f);
			
			/// memory usage
			size_t getMemory() const;
	};
	
	/**
	 * The MeshAttachment class represents an attachment that can be associated with a mesh node in a 3D scene.
	 * It supports various attachment types, including lights and cameras, allowing for flexible scene composition.
	 * The class provides methods for setting and retrieving the attachment type, name, associated node, and parameters.
	 * Each attachment can have custom parameters, such as boolean flags, scalar values, vectors, and colors, which can be added, accessed, and modified.
	 */
	class TS_API MeshAttachment {
			
			friend class MeshNode;
			
			TS_DECLARE_PTR(MeshAttachment, 0)
			
		public:
			
			/// Attachment types
			enum Type {
				TypeUnknown = 0,
				TypeLightGlobal,			// global light
				TypeLightPoint,				// point light
				TypeLightSpot,				// spot light
				TypeLightImage,				// image light
				TypeCameraPerspective,		// perspective camera
				TypeCameraOrthographic,		// orthographic camera
				NumTypes,
			};
			
			/// Attachment flags
			enum Flags {
				FlagNone = 0,
				FlagBool		= (1 << 0),		// boolean parameter flag
				FlagScalarf32	= (1 << 1),		// scalar parameter flag
				FlagVector4f	= (1 << 2),		// vector parameter flag
				FlagColor		= (1 << 3),		// color parameter flag
				FlagName		= (1 << 4),		// name parameter flag
			};
			
			explicit MeshAttachment(const char *name = nullptr);
			explicit MeshAttachment(Type type, const char *name = nullptr);
			explicit MeshAttachment(MeshNode &node, const char *name = nullptr);
			
			/// clear attachment
			void clear();
			
			/// attachment type
			void setType(Type type);
			Type getType() const;
			
			static const char *getTypeName(Type type);
			const char *getTypeName() const;
			
			TS_INLINE bool isUnknown() const { return (getType() == TypeUnknown); }
			TS_INLINE bool isLight() const { return (getType() >= TypeLightGlobal && getType() <= TypeLightSpot); }
			TS_INLINE bool isCamera() const { return (getType() >= TypeCameraPerspective && getType() <= TypeCameraOrthographic); }
			
			/// attachment name
			void setName(const char *name);
			String getName() const;
			
			/// attachment node
			void setNode(MeshNode &node, bool check = true);
			const MeshNode getNode() const;
			MeshNode getNode();
			
			/// attachment data
			void setData(const char *data);
			void setData(const String &data);
			String getData() const;
			
			/// attachment parameters
			void clearParameters();
			bool removeParameter(const char *type);
			void copyParameters(const MeshAttachment &attachment);
			uint32_t findParameter(const char *type) const;
			bool hasParameter(const char *type) const;
			
			uint32_t getNumParameters() const;
			String getParameterType(uint32_t index) const;
			
			/// add attachment parameters
			void addParameter(const char *type, bool value);
			void addParameter(const char *type, float32_t value);
			void addParameter(const char *type, const Vector4f &vector);
			void addParameter(const char *type, const Color &color);
			
			void addParameter(const char *type, const char *name);
			void addParameter(const char *type, const String &name);
			
			/// get attachment parameter by index
			Flags getParameterFlags(uint32_t index) const;
			bool hasParameterFlag(uint32_t index, Flags flags) const;
			bool hasParameterFlags(uint32_t index, Flags flags) const;
			
			bool getParameterBool(uint32_t index, bool value = false) const;
			float32_t getParameterScalarf32(uint32_t index, float32_t value = 0.0f) const;
			const Vector4f &getParameterVector4f(uint32_t index, const Vector4f &vector = Vector4f::zero) const;
			const Color &getParameterColor(uint32_t index, const Color &color = Color::white) const;
			String getParameterName(uint32_t index, const String &name = String::null) const;
			
			/// get attachment parameter by type
			Flags getParameterFlags(const char *type) const;
			bool hasParameterFlag(const char *type, Flags flags) const;
			bool hasParameterFlags(const char *type, Flags flags) const;
			
			bool getParameterBool(const char *type, bool value = false) const;
			float32_t getParameterScalarf32(const char *type, float32_t value = 0.0f) const;
			const Vector4f &getParameterVector4f(const char *type, const Vector4f &vector = Vector4f::zero) const;
			const Color &getParameterColor(const char *type, const Color &color = Color::white) const;
			String getParameterName(const char *type, const String &name = String::null) const;
			
			/// attachment transform
			void setTransform(const Vector3f &scale);
			void setTransform(const Matrix4x3f &transform);
			const Matrix4x3f &getTransform() const;
			
			/// compare attachments
			int32_t compare(const MeshAttachment &attachment) const;
			
			/// memory usage
			size_t getMemory() const;
			
			/// light parameter types
			static const char *TypeColor;
			static const char *TypeIntensity;
			static const char *TypeTemperature;
			static const char *TypeInnerAngle;
			static const char *TypeOuterAngle;
			static const char *TypeAttenuation;
			static const char *TypeDiffuse;
			static const char *TypeSpecular;
			static const char *TypeWidth;
			static const char *TypeHeight;
			static const char *TypeRadius;
			static const char *TypeLength;
			static const char *TypeShadow;
			
			/// camera parameter types
			static const char *TypeAspect;
			static const char *TypeFovX;
			static const char *TypeFovY;
			static const char *TypeSizeX;
			static const char *TypeSizeY;
			static const char *TypeZNear;
			static const char *TypeZFar;
			static const char *TypeFStop;
			static const char *TypeExposure;
			static const char *TypeApertureX;
			static const char *TypeApertureY;
			static const char *TypeFocalLength;
			static const char *TypeFocusDistance;
	};
	
	/**
	 * The Mesh class provides a comprehensive interface for loading, saving, editing, and optimizing 3D mesh data.
	 * It supports operations on mesh components such as nodes, geometries, animations, and bounding boxes.
	 * The class enables loading from file names or streams with optional asynchronous processing.
	 * It offers methods to validate mesh structure, set coordinate system bases, and manage transformation hierarchies.
	 * The class includes optimization features such as index reordering, attribute unification, material deduplication, and transform simplification.
	 * Additionally, it supports mesh packing, attribute compression, and applying scale transformations, making it a versatile tool for preparing and managing complex 3D models efficiently.
	 */
	class TS_API Mesh {
			
			TS_DECLARE_PTR(Mesh, 0)
			
		public:
			
			/// Mesh flags
			enum Flags {
				FlagNone = 0,
				FlagEmbed = (1 << 0),	// embed resources
				Flag32Bit = (1 << 1),	// 32-bit precision
			};
			
			Mesh();
			
			/// clear mesh
			void clear();
			
			/// check mesh
			bool isLoaded() const;
			
			/// info mesh
			bool info(const char *name, Flags flags = FlagNone, Async *async = nullptr);
			bool info(const String &name, Flags flags = FlagNone, Async *async = nullptr);
			bool info(Stream &stream, Flags flags = FlagNone, Async *async = nullptr);
			
			bool info(const char *name, Async *async) { return info(name, FlagNone, async); }
			bool info(const String &name, Async *async) { return info(name, FlagNone, async); }
			bool info(Stream &stream, Async *async) { return info(stream, FlagNone, async); }
			
			/// load mesh
			bool load(const char *name, Flags flags = FlagNone, Async *async = nullptr);
			bool load(const String &name, Flags flags = FlagNone, Async *async = nullptr);
			bool load(Stream &stream, Flags flags = FlagNone, Async *async = nullptr);
			
			bool load(const char *name, Async *async) { return load(name, FlagNone, async); }
			bool load(const String &name, Async *async) { return load(name, FlagNone, async); }
			bool load(Stream &stream, Async *async) { return load(stream, FlagNone, async); }
			
			/// save mesh
			bool save(const char *name, Flags flags = FlagNone) const;
			bool save(const String &name, Flags flags = FlagNone) const;
			bool save(Stream &stream, Flags flags = FlagNone) const;
			
			/// mesh name
			void setName(const char *name);
			String getName() const;
			
			/// mesh basis
			enum Basis {
				BasisUnknown = 0,	// front right up
				BasisXUpRight,		//   +Y    +Z  +X
				BasisYUpRight,		//   +Z    +X  +Y
				BasisZUpRight,		//   +X    +Y  +Z
				BasisXUpLeft,		//   +Y    -Z  +X
				BasisYUpLeft,		//   +Z    -X  +Y
				BasisZUpLeft,		//   +X    -Y  +Z
				BasisZUpMaya,		//   -Y    +X  +Z
				NumBases,
			};
			
			enum Axis {
				AxisUnknown = 0,
				AxisPX, AxisPY, AxisPZ,
				AxisNX, AxisNY, AxisNZ,
				NumAxes,
			};
			
			/// brep basis
			bool setBasis(Axis front, Axis right, Axis up);
			bool setBasis(Basis basis);
			
			Axis getFrontAxis() const;
			Axis getRightAxis() const;
			Axis getUpAxis() const;
			Basis getBasis() const;
			
			const char *getFrontAxisName() const;
			const char *getRightAxisName() const;
			const char *getUpAxisName() const;
			String getBasisName() const;
			
			/// mesh nodes
			void clearNodes();
			void reserveNodes(uint32_t num_nodes);
			uint32_t addNode(MeshNode &node, bool check = true);
			bool removeNode(MeshNode &node);
			uint32_t findNode(const MeshNode &node) const;
			uint32_t findNode(const char *name) const;
			
			uint32_t getNumNodes() const;
			const Array<MeshNode> getNodes() const;
			Array<MeshNode> getNodes();
			const MeshNode getNode(uint32_t index) const;
			MeshNode getNode(uint32_t index);
			
			/// create node transformations
			/// \param itransform Global to Local transformation matrix
			/// \param transform Local to Global transformation matrix
			void createLocalTransforms(const Matrix4x3d &itransform = Matrix4x3d::identity);
			void createGlobalTransforms(const Matrix4x3d &transform = Matrix4x3d::identity);
			
			/// mesh geometries
			void clearGeometries();
			void reserveGeometries(uint32_t num_geometries);
			uint32_t addGeometry(MeshGeometry &geometry, bool check = true);
			uint32_t addGeometry(MeshGeometry &geometry, MeshNode &node, bool check = true);
			bool removeGeometry(MeshGeometry &geometry);
			bool replaceGeometry(MeshGeometry &old_geometry, MeshGeometry &geometry);
			uint32_t findGeometry(const MeshGeometry &geometry) const;
			uint32_t findGeometry(const char *name) const;
			
			uint32_t getNumGeometries() const;
			const Array<MeshGeometry> getGeometries() const;
			Array<MeshGeometry> getGeometries();
			const MeshGeometry getGeometry(uint32_t index) const;
			MeshGeometry getGeometry(uint32_t index);
			
			bool hasGeometryIndices(MeshIndices::Type type) const;
			bool hasGeometryAttribute(MeshAttribute::Type type) const;
			
			size_t getNumGeometryPositions() const;
			size_t getNumGeometryPrimitives() const;
			
			/// mesh animations
			void clearAnimations();
			void reserveAnimations(uint32_t num_animations);
			uint32_t addAnimation(MeshAnimation &animation, bool check = true);
			bool removeAnimation(MeshAnimation &animation);
			bool replaceAnimation(MeshAnimation &old_animation, MeshAnimation &animation);
			uint32_t findAnimation(const MeshAnimation &animation) const;
			uint32_t findAnimation(const char *name) const;
			
			uint32_t getNumAnimations() const;
			const Array<MeshAnimation> getAnimations() const;
			Array<MeshAnimation> getAnimations();
			const MeshAnimation getAnimation(uint32_t index) const;
			MeshAnimation getAnimation(uint32_t index);
			
			/// mesh bound box
			BoundBoxd getBoundBox() const;
			BoundBoxd getBoundBox(const MeshNode &node) const;
			BoundBoxd getBoundBox(const MeshGeometry &geometry) const;
			
			/// create bounds
			/// \param force Force bounding creation.
			bool createBounds(bool force, Async *async = nullptr);
			bool createBounds(Async *async = nullptr) { return createBounds(false, async); }
			
			/// create tangent basis
			/// \param force Force basis creation.
			bool createBasis(bool force, Async *async = nullptr);
			bool createBasis(float32_t angle, bool force, Async *async = nullptr);
			bool createBasis(Async *async = nullptr) { return createBasis(false, async); }
			bool createBasis(float32_t angle, Async *async = nullptr) { return createBasis(angle, false, async); }
			
			/// create normals
			/// \param force Force normals creation.
			/// \param angle Smoothing angle in degrees.
			bool createNormals(bool force, Async *async = nullptr);
			bool createNormals(float32_t angle, bool force, Async *async = nullptr);
			bool createNormals(Async *async = nullptr) { return createNormals(false, async); }
			bool createNormals(float32_t angle, Async *async = nullptr) { return createNormals(angle, false, async); }
			
			/// create tangents
			/// \param force Force tangents creation.
			bool createTangents(bool force, Async *async = nullptr);
			bool createTangents(Async *async = nullptr) { return createTangents(false, async); }
			
			/// create islands
			/// \param max_attributes Maximum number of attributes per island.
			/// \param max_primitives Maximum number of primitives per island.
			/// \param force Force islands creation.
			bool createIslands(uint32_t max_attributes, uint32_t max_primitives, bool force, Async *async = nullptr);
			bool createIslands(uint32_t max_attributes, uint32_t max_primitives, Async *async = nullptr) { return createIslands(max_attributes, max_primitives, false, async); }
			
			/// optimize indices order for cache
			bool optimizeIndices(uint32_t cache, bool transparent, Async *async = nullptr);
			bool optimizeIndices(Async *async = nullptr) { return optimizeIndices(32, false, async); }
			bool optimizeIndices(uint32_t cache, Async *async = nullptr) { return optimizeIndices(cache, false, async); }
			
			/// optimize attributes and make single indices.
			bool optimizeAttributes(Async *async = nullptr);
			
			/// optimize materials remove duplicates
			void optimizeMaterials();
			
			/// optimize winding based on node transforms
			/// \param clockwise Optimize for clockwise winding.
			bool optimizeWinding(bool clockwise = false);
			
			/// optimize geometries remove duplicates
			/// \param threshold Spatial compare threshold.
			/// \param depth Number of geometries to compare.
			void optimizeGeometries(float32_t threshold = 1e-3f, uint32_t depth = 16);
			
			/// optimize animation transforms
			/// \param threshold Compare threshold.
			void optimizeAnimations(float32_t threshold = 1e-6f);
			
			/// optimize node and geometry order
			bool optimizeOrder();
			
			/// merge geometries
			void mergeGeometries();
			
			/// pack attributes
			bool packAttributes(bool remove = true);
			bool unpackAttributes(bool remove = true);
			
			/// apply transform
			bool setTransform(const Vector3d &scale);
			
			/// memory usage
			size_t getMemory() const;
	};
	
	/**
	 * The MeshStream class is a base class designed for creating custom mesh stream formats, providing virtual methods for loading and saving meshes through streams.
	 * It supports handling different mesh types and formats, serving as a foundation for implementing specific mesh stream formats and enabling the customization and extension of mesh handling functionality.
	 * The class also includes static methods for checking supported formats and retrieving lists of compatible load and save formats, offering flexibility in managing and working with various mesh stream formats.
	 */
	class TS_API MeshStream {
			
			TS_DECLARE_NONCOPY(MeshStream, 0)
			
		protected:
			
			enum Flags {
				FlagNone = 0,
				FlagLoad		= (1 << 0),
				FlagSave		= (1 << 1),
				FlagLoadSave	= (FlagLoad | FlagSave),
			};
			
			MeshStream(Flags flags, const char *name, uint32_t magic = 0);
			MeshStream(Flags flags, const InitializerList<const char*> &names, uint32_t magic = 0);
			MeshStream(Flags flags, const InitializerList<const char*> &names, const InitializerList<uint32_t> &magics);
			
		public:
			
			virtual Mesh::Basis getBasis() const { return Mesh::BasisUnknown; }
			
			virtual bool info(Stream &stream, Mesh &mesh, Mesh::Flags flags, Async *async);
			virtual bool load(Stream &stream, Mesh &mesh, Mesh::Flags flags, Async *async);
			virtual bool save(Stream &stream, const Mesh &mesh, Mesh::Flags flags);
			
			/// mesh stream formats
			static bool check(const String &name, uint32_t magic = 0);
			
			/// list of supported formats
			static String getLoadFormats();
			static String getSaveFormats();
	};
	
	/*
	 */
	TS_DECLARE_ENUM_OP(MeshMaterial::Flags)
	TS_DECLARE_ENUM_OP(Mesh::Flags)
}

#endif /* __TELLUSIM_FORMAT_MESH_H__ */
