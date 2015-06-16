//�摜��r�p2�����摜���i�[�N���X
//c++��template�g�p
//000417
//�g�����F�܂��ŏ���allocate���āC�̈�m�ۂ��Ă���C
//cell_array,flag_array�Ƀf�[�^������Ηǂ�

//operator=����`����Ă���^�łȂ��Ɨv�f�ɂȂ�Ȃ�
//---------------------------------------------------------------------------
#ifndef matrix2dH
#define matrix2dH
template <class T> struct Matrix2D
{
T *cell_array;//2������f�ւ̃|�C���^�D�����z��ɂ��Ďg���D
char *flag_array;//�f�[�^�����邩�Ȃ���
int mesh_i,mesh_j;//���b�V���̐�
char allocate_flag;//�f�[�^�̈�m�ۃt���O

char allocate(int mesh_i_in,int mesh_j_in);//�̈�m��
char write(T cell,int i_in,int j_in);//����
char read(T *cell,int i_in,int j_in);//�o��
char check(int i_in,int j_in);//���b�V���̐��͈̔͂ɓ����Ă��邩�ǂ���
int index(int i_in,int j_in);
//���჌�x���A�N�Z�X�p�C���f�b�N�X�֐��D�ł��邾���g��Ȃ��悤�ɂ���D
//�g�p���ɂ̓t���O�ɒ���
Matrix2D(void);//�R���X�g���N�^

void operator=(const Matrix2D<T>& rhs);//����֐�
};
//�N���A�֐�����肽���������C�ėp���̂��߁C���Ȃ����Ƃɂ���000417
//---------------------------------------------------------------------------
//�e���v���[�g�Ȃ̂ŁC�֐����S���C���N���[�h���Ă��Ȃ��Ƃ����Ȃ��炵���D
//---------------------------------------------------------------------------
#endif
 